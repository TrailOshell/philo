/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:57:55 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/20 12:07:42 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_process(t_data *data, int process)
{
	pthread_mutex_lock(&data->mute_process);
	data->process = process;
	pthread_mutex_unlock(&data->mute_process);
}

void	set_state(t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->mute_state);
	philo->state = state;
	pthread_mutex_unlock(&philo->mute_state);
}

void	set_n_eaten(t_philo *philo, int n_eaten)
{
	pthread_mutex_lock(&philo->mute_n_eaten);
	philo->n_eaten = n_eaten;
	pthread_mutex_unlock(&philo->mute_n_eaten);
}

void	set_satisfied(t_philo *philo, int is_satisfied)
{
	pthread_mutex_lock(&philo->mute_satisfied);
	philo->is_satisfied = is_satisfied;
	pthread_mutex_unlock(&philo->mute_satisfied);
}

void	set_last_meal_time(t_philo *philo, unsigned long timestamp)
{
	pthread_mutex_lock(&philo->mute_last_meal_time);
	philo->last_meal_time = timestamp;
	pthread_mutex_unlock(&philo->mute_last_meal_time);
}
