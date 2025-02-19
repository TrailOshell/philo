/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:36:22 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/19 19:21:27 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dying(t_data *data, t_philo *philo)
{
	if (get_timestamp(data) - get_last_meal_time(philo)
		>= (data->t_die / 1000) + 10)
	{
		set_state(data, philo, DEAD);
		print_timestamp(data, philo->id, get_state(philo));
		return (1);
	}
	return (0);
}
	// if (get_process(data) != RUNNING)
	// 	return (1);

void	notify_all_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = data->philos;
	i = 0;
	while (i < data->n_philos)
		set_state(data, &philos[i++], DEAD);
}

//	monitor each philosopher to check if one died, or all have ate enough food
void	*monitor_dying(void *data_arg)
{
	t_data	*data;
	t_philo	*philos;
	int		i;
	int		n_philos;

	data = (t_data *)data_arg;
	philos = data->philos;
	n_philos = data->n_philos;
	i = 0;
	while (get_process(data) == RUNNING)
	{
		if (dying(data, &philos[i++]) == 1)
		{
			pthread_mutex_lock(&data->mute_philo);
			set_process(data, PHILO_DIED);
			notify_all_philos(data);
			pthread_mutex_unlock(&data->mute_philo);
			pthread_mutex_lock(&data->mute_print);
			printf(RED"MONITOR: DEAD\n"NO_CLR);
			pthread_mutex_unlock(&data->mute_print);
			break ;
		}
		if (i == n_philos)
			i = 0;
		usleep(1000);
	}
	return (NULL);
}

void	*monitor_all_full(void *data_arg)
{
	t_data	*data;
	t_philo	*philos;
	int		i;

	data = (t_data *)data_arg;
	philos = data->philos;
	if (data->n_philos_eat == 0)
		return (NULL);
	i = 0;
	while (i < data->n_philos && get_process(data) == RUNNING)
	{
		if (get_satisfied(&philos[i++]) == 0)
			i = 0;
		usleep(1000);
	}
	if (get_process(data) == RUNNING)
	{
		pthread_mutex_lock(&data->mute_philo);
		set_process(data, ALL_FULL);
		notify_all_philos(data);
		pthread_mutex_unlock(&data->mute_philo);
	}
	if (get_process(data) == ALL_FULL)
	{
		pthread_mutex_lock(&data->mute_print);
		printf(BLU"MONITOR: FULL\n"NO_CLR);
		pthread_mutex_unlock(&data->mute_print);
	}
	notify_all_philos(data);
	return (NULL);
}
