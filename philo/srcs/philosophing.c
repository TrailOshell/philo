/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:58:05 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/14 04:57:14 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	drop_forks(t_data *data, t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}

static int	thinking(t_data *data, t_philo *philo)
{
	if (philo->state != THINKING)
	{
		philo->state = THINKING;
		print_timestamp(data, *philo);
	}
	return (1);
}

static int	eating(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	if (data->process != RUNNING)
	{
		pthread_mutex_unlock(philo->fork_left);
		return (0);
	}
	philo->state = FORKING;
	print_timestamp(data, *philo);
	pthread_mutex_lock(philo->fork_right);
	if (data->process != RUNNING)
		return (drop_forks(data, philo));
	print_timestamp(data, *philo);
	db_thread_locking(data, philo, YLW"locked"NO_CLR);
	if (data->process != RUNNING)
		return (drop_forks(data, philo));
	philo->state = EATING;
	print_timestamp(data, *philo);
	usleep(data->t_eat);
	drop_forks(data, philo);
	philo->last_meal_time = get_timestamp(data->time_start);
	philo->n_eaten += 1;
	if (philo->n_eaten >= data->n_philos_eat)
		philo->is_satisfied = 1;
	db_thread_locking(data, philo, GRN"unlocked"NO_CLR);
	return (1);
}

static int	sleeping(t_data *data, t_philo *philo)
{
	philo->state = SLEEPING;
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
	philo->state = THINKING;
	print_timestamp(data, *philo);
	if (data->n_philos == 1)
	{
		philo->state = FORKING;
		print_timestamp(data, *philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(5000);
	while (philo->state != DEAD && data->process == RUNNING)
	{
		if (thinking(data, philo) != 1 || data->process != RUNNING)
			break ;
		if (eating(data, philo) != 1 || data->process != RUNNING)
			break ;
		if (sleeping(data, philo) != 1 || data->process != RUNNING)
			break ;
	}
	return (NULL);
}
