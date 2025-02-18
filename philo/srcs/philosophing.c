/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:58:05 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/18 15:30:45y tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	thinking(t_data *data, t_philo *philo)
{
	if (get_state(philo) != THINKING)
	{
		set_state(data, philo, THINKING);
		if (get_process(data) == RUNNING)
			print_timestamp(data, philo->id, get_state(philo));
	}
	return (1);
}

static int	eating(t_data *data, t_philo *philo)
{
	if (take_first_fork(get_process(data), philo) != 1)
		return (0);
	if (get_process(data) != RUNNING)
		{ pthread_mutex_lock(&data->mute_print); printf(YLW"first fork\n"NO_CLR); pthread_mutex_unlock(&data->mute_print); }
	set_state(data, philo, FORKING);
	if (get_process(data) == RUNNING)
		print_timestamp(data, philo->id, get_state(philo));
	if (take_second_fork(get_process(data), philo) != 1)
	{
		drop_first_fork(philo);
		return (0);
	}
	if (get_process(data) != RUNNING)
		return (drop_forks(philo));
	if (get_process(data) == RUNNING)
		print_timestamp(data, philo->id, get_state(philo));
	db_thread_locking(data, philo, YLW"locked"NO_CLR);
	if (get_process(data) != RUNNING)
		return (drop_forks(philo));
	set_state(data, philo, EATING);
	if (get_process(data) == RUNNING)
		print_timestamp(data, philo->id, get_state(philo));
	usleep(data->t_eat);
	set_last_meal_time(data, philo);
	set_n_eaten(philo, get_n_eaten(philo) + 1);
	if (get_n_eaten(philo) >= data->n_philos_eat)
		set_satisfied(philo, 1);
	drop_forks(philo);
	db_thread_locking(data, philo, GRN"unlocked"NO_CLR);
	return (1);
}

static int	sleeping(t_data *data, t_philo *philo)
{
	set_state(data, philo, SLEEPING);
	print_timestamp(data, philo->id, get_state(philo));
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
	print_timestamp(data, philo->id, get_state(philo));
	if (data->n_philos == 1)
	{
		set_state(data, philo, FORKING);
		print_timestamp(data, philo->id, get_state(philo));
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(data->t_eat);
	while (get_state(philo) != DEAD && get_process(data) == RUNNING)
	{
		if (thinking(data, philo) == 0 || get_process(data) != RUNNING)
			break ;
		if (eating(data, philo) != 1 || get_process(data) != RUNNING)
			break ;
		if (sleeping(data, philo) != 1 || get_process(data) != RUNNING)
			break ;
	}
	return (NULL);
}
		//if (get_process(data) != RUNNING)
		//	break ;
