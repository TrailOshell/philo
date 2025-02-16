/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:37:00 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/16 10:50:43 by tsomchan         ###   ########.fr       */
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

void	set_print_state(t_data *data, t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->mute_state);
	philo->state = state;
	pthread_mutex_unlock(&philo->mute_state);
	print_timestamp(data, *philo);
}

int	get_process(t_data *data)
{
	int	process;

	pthread_mutex_lock(&data->mute_process);
	process = data->process;
	pthread_mutex_unlock(&data->mute_process);
	return (process);
}

void	set_process(t_data *data, int process)
{
	pthread_mutex_lock(&data->mute_process);
	data->process = process;
	pthread_mutex_unlock(&data->mute_process);
}

int	get_satisfied(t_philo *philo)
{
	int	is_satisfied;

	pthread_mutex_lock(&philo->mute_satisfied);
	is_satisfied = philo->is_satisfied;
	pthread_mutex_unlock(&philo->mute_satisfied);
	return (is_satisfied);
}

void	set_satisfied(t_philo *philo, int is_satisfied)
{
	pthread_mutex_lock(&philo->mute_satisfied);
	philo->is_satisfied = is_satisfied;
	pthread_mutex_unlock(&philo->mute_satisfied);
}

int	get_last_meal_time(t_philo *philo)
{
	int	meal_time;

	pthread_mutex_lock(&philo->mute_last_meal_time);
	meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->mute_last_meal_time);
	return (meal_time);
}

void	set_last_meal_time(t_philo *philo, unsigned long meal_time)
{
	pthread_mutex_lock(&philo->mute_last_meal_time);
	philo->last_meal_time = meal_time;
	pthread_mutex_unlock(&philo->mute_last_meal_time);
}
