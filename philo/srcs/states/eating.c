/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:19:13 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/08 22:00:35 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ate_a_dish(t_data *data, t_philo *philo)
{
	philo->n_eaten += 1;
	if (philo->n_eaten >= data->n_philos_eat)
		philo->is_satisfied = 1;
}

int	eating(t_data *data, t_philo *philo)
{
	philo->state = EATING;
	print_timestamp(data, *philo);
	micro_sleeping(data, data->t_eat);
	if (data->process_state != RUNNING)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (1);
	}
	philo->last_meal_time = get_timestamp(data->time_start);
	ate_a_dish(data, philo);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	db_thread_locking(data, philo, GRN"unlocked"NO_CLR);
	return (0);
}
