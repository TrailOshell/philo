/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:58:05 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/19 21:15:57by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	forking(t_data *data, t_philo *philo)
{
	if (take_first_fork(philo) != 1)
		return (1);
	print_timestamp(data, philo->id, FORKING);
	if (take_second_fork(philo) != 1)
		return (drop_first_fork(philo));
	print_timestamp(data, philo->id, FORKING);
	return (0);
}
	// db_thread_locking(data, philo, YLW"locked"NO_CLR);

static int	eating(t_data *data, t_philo *philo)
{
	int	n_eaten;

	if (get_state(philo) == DEAD)
		return (drop_forks(philo));
	print_timestamp(data, philo->id, EATING);
	usleep(data->t_eat);
	set_last_meal_time(philo, get_timestamp(data));
	n_eaten = get_n_eaten(philo) + 1;
	set_n_eaten(philo, n_eaten);
	if (n_eaten >= data->n_philos_eat)
		set_satisfied(philo, 1);
	drop_forks(philo);
	return (0);
}
	// db_thread_locking(data, philo, GRN"unlocked"NO_CLR);

static int	sleeping(t_data *data, t_philo *philo)
{
	print_timestamp(data, philo->id, SLEEPING);
	if (data->t_sleep >= data->t_die)
		usleep(data->t_die);
	else
		usleep(data->t_sleep);
	return (0);
}

static int	thinking(t_data *data, t_philo *philo)
{
	print_timestamp(data, philo->id, THINKING);
	return (0);
}

//	The main thread for each philosophers
void	*philosophing(void *philo_arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_arg;
	data = philo->data;
	if (data->n_philos == 1)
	{
		print_timestamp(data, philo->id, FORKING);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(data->t_eat);
	while (get_state(philo) != DEAD)
	{
		if (forking(data, philo) == 1)
			break ;
		if (eating(data, philo) == 1 || get_state(philo) == DEAD)
			break ;
		if (sleeping(data, philo) == 1 || get_state(philo) == DEAD)
			break ;
		if (thinking(data, philo) == 1)
			break ;
	}
	return (NULL);
}
		//if (get_process(data) != RUNNING)
		//	break ;
	// if (get_state(philo) == DEAD)
	// {
	// 	pthread_mutex_lock(&data->mute_print);
	// 	printf(YLW"THREAD: DEAD\n"NO_CLR);
	// 	pthread_mutex_unlock(&data->mute_print);
	// }
	// printf(YLW"THREAD: STATE = %d\n"NO_CLR, philo->state);
