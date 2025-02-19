/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:58:05 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/19 19:21:38 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	forking(t_data *data, t_philo *philo)
{
	if (data->n_philos == 1)
	{
		set_state(data, philo, FORKING);
		print_timestamp(data, philo->id, get_state(philo));
		return (1);
	}
	if (take_first_fork(get_process(data), philo) != 1)
		return (1);
	set_state(data, philo, FORKING);
	print_timestamp(data, philo->id, get_state(philo));
	if (take_second_fork(get_process(data), philo) != 1)
	{
		drop_first_fork(philo);
		return (1);
	}
	if (get_process(data) != RUNNING || get_state(philo) == DEAD)
		return (drop_forks(philo));
	print_timestamp(data, philo->id, get_state(philo));
	db_thread_locking(data, philo, YLW"locked"NO_CLR);
	if (get_process(data) != RUNNING || get_state(philo) == DEAD)
		return (drop_forks(philo));
	return (0);
}

static int	eating(t_data *data, t_philo *philo)
{
	set_state(data, philo, EATING);
	print_timestamp(data, philo->id, get_state(philo));
	usleep(data->t_eat);
	set_last_meal_time(data, philo);
	set_n_eaten(philo, get_n_eaten(philo) + 1);
	if (get_n_eaten(philo) >= data->n_philos_eat)
		set_satisfied(philo, 1);
	drop_forks(philo);
	db_thread_locking(data, philo, GRN"unlocked"NO_CLR);
	return (0);
}
	//if (get_process(data) != RUNNING && get_state(philo) != DEAD)
	//	{ pthread_mutex_lock(&data->mute_print);
	// printf(YLW"first fork\n"NO_CLR);
	// pthread_mutex_unlock(&data->mute_print); }

static int	sleeping(t_data *data, t_philo *philo)
{
	set_state(data, philo, SLEEPING);
	print_timestamp(data, philo->id, get_state(philo));
	if (data->t_sleep >= data->t_die)
		usleep(data->t_die);
	else
		usleep(data->t_sleep);
	return (0);
}

static int	thinking(t_data *data, t_philo *philo)
{
	set_state(data, philo, THINKING);
	print_timestamp(data, philo->id, get_state(philo));
	return (0);
}

//	The main thread for each philosophers
void	*philosophing(void *philo_arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_arg;
	data = philo->data;
	if (philo->id % 2 == 0)
		usleep(data->t_eat);
	while (get_state(philo) != DEAD && get_process(data) == RUNNING)
	{
		if (forking(data, philo) == 1)
			break ;
		if (get_process(data) != RUNNING || get_state(philo) == DEAD)
			break ;
		if (eating(data, philo) == 1)
			break ;
		if (get_process(data) != RUNNING || get_state(philo) == DEAD)
			break ;
		if (sleeping(data, philo) == 1)
			break ;
		if (get_process(data) != RUNNING || get_state(philo) == DEAD)
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
