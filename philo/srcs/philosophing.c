/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:58:05 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/16 15:33:59 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}

static int	thinking(t_data *data, t_philo *philo)
{
	if (get_state(philo) != THINKING)
	{
		set_print_state(data, philo, THINKING);
		print_timestamp(data, *philo);
	}
	return (1);
}

static int	eating(t_data *data, t_philo *philo)
{
	if (get_process(data) != RUNNING)
		return (0);
	pthread_mutex_lock(philo->fork_left);
	set_print_state(data, philo, FORKING);
	print_timestamp(data, *philo);
	if (get_process(data) != RUNNING)
	{
		pthread_mutex_unlock(philo->fork_left);
		return (0);
	}
	pthread_mutex_lock(philo->fork_right);
	if (get_process(data) != RUNNING)
		return (drop_forks(philo));
	print_timestamp(data, *philo);
	db_thread_locking(data, philo, YLW"locked"NO_CLR);
	if (get_process(data) != RUNNING)
		return (drop_forks(philo));
	set_print_state(data, philo, EATING);
	print_timestamp(data, *philo);
	usleep(data->t_eat);
	drop_forks(philo);
	set_last_meal_time(data, philo);
	set_n_eaten(philo, get_n_eaten(philo) + 1);
	if (get_n_eaten(philo) >= data->n_philos_eat)
		set_satisfied(philo, 1);
	db_thread_locking(data, philo, GRN"unlocked"NO_CLR);
	return (1);
}

static int	sleeping(t_data *data, t_philo *philo)
{
	set_print_state(data, philo, SLEEPING);
	print_timestamp(data, *philo);
	if (data->t_sleep >= data->t_die)
	{
		usleep(data->t_die);
		return (0);
	}
	usleep(data->t_sleep);
	return (1);
}

//	The main thread for each philosophers
void	*philosophing(void *philo_arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_arg;
	data = philo->data;
	print_timestamp(data, *philo);
	if (data->n_philos == 1)
	{
		set_print_state(data, philo, FORKING);
		print_timestamp(data, *philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(5000);
	while (get_state(philo) != DEAD && get_process(data) == RUNNING)
	{
		if (thinking(data, philo) != 1 || get_process(data) != RUNNING)
			break ;
		if (eating(data, philo) != 1 || get_process(data) != RUNNING)
			break ;
		if (sleeping(data, philo) != 1 || get_process(data) != RUNNING)
			break ;
	}
	return (NULL);
}
