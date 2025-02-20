/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:58:05 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/20 15:12:30 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	forking(t_data *data, t_philo *philo)
{
	if (take_first_fork(data, philo) != 1)
		return (1);
	set_state(philo, FORKING);
	print_running_timestamp(data, philo->id, FORKING);
	if (take_second_fork(data, philo) != 1)
		return (drop_first_fork(data, philo));
	print_running_timestamp(data, philo->id, FORKING);
	return (0);
}

static int	eating(t_data *data, t_philo *philo)
{
	int	n_eaten;

	if (get_process(data) != RUNNING)
		return (drop_forks(data, philo));
	set_state(philo, EATING);
	print_running_timestamp(data, philo->id, EATING);
	if (data->t_eat >= data->t_die)
	{
		usleep(data->t_die);
		return (drop_forks(data, philo));
	}
	usleep(data->t_eat);
	set_last_meal_time(philo, get_timestamp(data));
	n_eaten = get_n_eaten(philo) + 1;
	set_n_eaten(philo, n_eaten);
	if (n_eaten >= data->n_philos_eat)
		set_satisfied(philo, 1);
	return (0);
}

static int	sleeping(t_data *data, t_philo *philo)
{
	set_state(philo, SLEEPING);
	print_running_timestamp(data, philo->id, SLEEPING);
	drop_forks(data, philo);
	if (data->t_sleep >= data->t_die)
		return (1);
	usleep(data->t_sleep);
	return (0);
}

static int	thinking(t_data *data, t_philo *philo)
{
	if (get_process(data) != RUNNING)
		return (1);
	set_state(philo, THINKING);
	print_running_timestamp(data, philo->id, THINKING);
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
		print_running_timestamp(data, philo->id, FORKING);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(data->t_eat);
	while (get_process(data) == RUNNING)
	{
		if (forking(data, philo) == 1)
			break ;
		if (eating(data, philo) == 1)
			break ;
		if (sleeping(data, philo) == 1)
			break ;
		if (thinking(data, philo) == 1)
			break ;
	}
	return (NULL);
}
