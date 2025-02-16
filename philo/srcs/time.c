/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:22:14 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/16 10:39:53 by tsomchan         ###   ########.fr       */
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
unsigned long	get_timestamp(unsigned long start)
{
	unsigned long	now;

	now = get_miliseconds();
	return (now - start);
}

void	print_timestamp(t_data *data, t_philo philo)
{
	unsigned long	timestamp;
	const char		*state[7] = {"is thinking", "has taken a fork", \
						"is eating", "is sleeping", "is full", "died"};

	timestamp = get_timestamp(data->time_start);
	pthread_mutex_lock(&data->mute_print);
	if (DEFAULT_PRINT)
		printf("%lu %d %s\n", timestamp, philo.id, state[philo.state]);
	pthread_mutex_unlock(&data->mute_print);
	db_check_all_states(data, philo.id, get_timestamp(data->time_start));
}
