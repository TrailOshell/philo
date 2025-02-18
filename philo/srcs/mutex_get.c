/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:37:00 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/18 14:59:36 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_state(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&philo->mute_state);
	state = philo->state;
	pthread_mutex_unlock(&philo->mute_state);
	return (state);
}

int	get_process(t_data *data)
{
	int	process;

	pthread_mutex_lock(&data->mute_process);
	process = data->process;
	pthread_mutex_unlock(&data->mute_process);
	return (process);
}

int	get_n_eaten(t_philo *philo)
{
	int	n_eaten;

	pthread_mutex_lock(&philo->mute_n_eaten);
	n_eaten = philo->n_eaten;
	pthread_mutex_unlock(&philo->mute_n_eaten);
	return (n_eaten);
}

int	get_satisfied(t_philo *philo)
{
	int	is_satisfied;

	pthread_mutex_lock(&philo->mute_satisfied);
	is_satisfied = philo->is_satisfied;
	pthread_mutex_unlock(&philo->mute_satisfied);
	return (is_satisfied);
}

unsigned long	get_last_meal_time(t_philo *philo)
{
	unsigned long	meal_time;

	pthread_mutex_lock(&philo->mute_last_meal_time);
	meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->mute_last_meal_time);
	return (meal_time);
}
