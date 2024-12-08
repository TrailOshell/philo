/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:22:14 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/08 21:57:49 by tsomchan         ###   ########.fr       */
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
		printf("%lu %d %s\n", timestamp, philo.id + 1, state[philo.state]);
	pthread_mutex_unlock(&data->mute_print);
	db_check_all_states(data, philo.id, get_timestamp(data->time_start));
}

int	micro_sleeping(t_data *data, unsigned long sleep)
{
	unsigned long sum;

	sum = 0;
	while (sum < sleep || data->process_state != RUNNING)
	{
		usleep(1000);
		sum += 1000;
	}
	// printf("sum= %lu\n", sum);
	return (0);
}