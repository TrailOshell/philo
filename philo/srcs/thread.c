/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:47:21 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/08 18:52:30 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philos_finish_must_eat(t_data *data)
{
	int	i;

	i = 0;
	if (data->n_philos_eat == 0)
		return (1);
	while (i < data->n_philos)
		if (data->philos[i++].is_satisfied == 0)
			return (1);
	return (0);
}

int	check_starvation(t_data *data, t_philo *philo)
{
	if (get_timestamp(data->time_start) - philo->last_meal_time
		>= data->t_die / 1000)
	{
		philo->state = DEAD;
		print_timestamp(data, *philo);
		data->process_state = PHILO_DIED;
		return (1);
	}
	return (0);
}

int	grabbing_forks(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	philo->state = FORKING;
	print_timestamp(data, *philo);
	pthread_mutex_lock(philo->fork_right);
	print_timestamp(data, *philo);
	db_thread_locking(data, philo, YLW"locked"NO_CLR);
	philo->state = EATING;
	eating(data, philo);
	philo->state = SLEEPING;
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	db_thread_locking(data, philo, GRN"unlocked"NO_CLR);
	return (0);
}

int	die_alone(t_data *data, t_philo *philo)
{
	if (data->n_philos == 1)
	{
		usleep(data->t_die);
		check_starvation(data, philo);
		return (1);
	}
	return (0);
}

//int	philosophing(t_data *data)
void	*philosophing(void *philo_arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_arg;
	data = philo->data;
	if (die_alone(data, philo) == 1)
		return (NULL);
	if (philo->id % 2 == 1)
		usleep(data->t_eat);
	while (philo->state != DEAD && data->process_state == RUNNING)
	{
		check_starvation(data, philo);
		if (philo->state == THINKING || philo->state == FORKING)
			grabbing_forks(data, philo);
		else if (philo->state == SLEEPING)
			sleeping(data, philo);
		check_starvation(data, philo);
	}
	if (DEBUG_THREADS_DONE == 1)
		printf(YLW "thread[%d] is done\n" NO_CLR, philo->id);
	return (NULL);
}
