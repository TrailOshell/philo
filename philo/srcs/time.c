/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:22:14 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/22 14:27:01 by tsomchan         ###   ########.fr       */
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

//	print the timestamp
void	print_timestamp(t_data *data, int id, int state)
{
	const char		*txt[7] = {"is thinking", "has taken a fork", \
						"is eating", "is sleeping", "died"};

	pthread_mutex_lock(&data->mute_print);
	if (DEFAULT_PRINT == 1)
		printf("%lu %d %s\n", get_timestamp(data), id, txt[state]);
	if (DB_PRINT == 1)
		db_check_all_ph(data, id, get_timestamp(data));
	pthread_mutex_unlock(&data->mute_print);
}

//	only print timestamp when main process is RUNNING
void	print_run_timestamp(t_data *data, int id, int state)
{
	pthread_mutex_lock(&data->mute_philo);
	if (get_process(data) == RUNNING)
		print_timestamp(data, id, state);
	pthread_mutex_unlock(&data->mute_philo);
}
