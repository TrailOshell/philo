/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:58:05 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/16 13:39:37 by tsomchan         ###   ########.fr       */
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
	if (get_state(philo) != THINKING)
	{
		set_print_state(data, philo, THINKING);
		print_timestamp(data, *philo);
	}
	return (1);
}

static int	eating(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	if (get_process(data) != RUNNING)
	{
		pthread_mutex_unlock(philo->fork_left);
		return (0);
	}
	set_print_state(data, philo, FORKING);
	print_timestamp(data, *philo);
	pthread_mutex_lock(philo->fork_right);
	if (get_process(data) != RUNNING)
		return (drop_forks(data, philo));
	print_timestamp(data, *philo);
	db_thread_locking(data, philo, YLW"locked"NO_CLR);
	if (get_process(data) != RUNNING)
		return (drop_forks(data, philo));
	set_print_state(data, philo, EATING);
	print_timestamp(data, *philo);
	usleep(get_t_eat(data));
	drop_forks(data, philo);
	set_last_meal_time(philo, get_timestamp(data));
	set_n_eaten(philo, get_n_eaten(philo) + 1);
	if (get_n_eaten(philo) >= get_n_philos_eat(data))
		set_satisfied(philo, 1);
	db_thread_locking(data, philo, GRN"unlocked"NO_CLR);
	return (1);
}

static int	sleeping(t_data *data, t_philo *philo)
{
	set_print_state(data, philo, SLEEPING);
	print_timestamp(data, *philo);
	if (get_t_sleep(data) >= get_t_die(data))
	{
		usleep(get_t_die(data));
		return (0);
	}
	usleep(get_t_sleep(data));
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
	if (get_n_philos(data) == 1)
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
