/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:58:05 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/08 20:08:28 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	die_alone(t_data *data, t_philo *philo)
{
	if (data->n_philos == 1)
	{
		usleep(data->t_die);
		check_starvation(data, philo);
		return (1);
	}
	return (0);
}

static	int	grabbing_forks(t_data *data, t_philo *philo)
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
