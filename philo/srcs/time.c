/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:22:14 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/19 19:24:42 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
//	gettimeofday() and then set it to miliseconds
unsigned long	get_miliseconds(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * (unsigned long)1000) + (tv.tv_usec / 1000));
}

// get timestamp since the program started
unsigned long	get_timestamp(t_data *data)
{
	unsigned long	now;

	pthread_mutex_lock(&data->mute_timestamp);
	now = get_miliseconds();
	pthread_mutex_unlock(&data->mute_timestamp);
	return (now - data->time_start);
}

void	print_timestamp(t_data *data, int id, int state)
{
	unsigned long	timestamp;
	const char		*txt[7] = {"is thinking", "has taken a fork", \
						"is eating", "is sleeping", "is full", "died"};

	pthread_mutex_lock(&data->mute_philo);
	pthread_mutex_lock(&data->mute_print);
	if (get_process(data) == RUNNING)
	{
		timestamp = get_timestamp(data);
		printf("%lu %d %s\n", timestamp, id, txt[state]);
	}
	pthread_mutex_unlock(&data->mute_print);
	pthread_mutex_unlock(&data->mute_philo);
}
	// pthread_mutex_lock(&data->mute_philo);
	// pthread_mutex_unlock(&data->mute_philo);
	//if (DEFAULT_PRINT)
	// db_check_all_states(data, id, timestamp);
