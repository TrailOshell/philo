/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:36:22 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/19 15:23:47 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dying(t_data *data, t_philo *philo)
{
	if (get_process(data) != RUNNING)
		return (1);
	if (get_timestamp(data) - get_last_meal_time(philo)
		>= (data->t_die / 1000) + 10)
	{
		set_state(data, philo, DEAD);
		print_timestamp(data, philo->id, get_state(philo));
		return (1);
	}
	return (0);
}

// void	notify_all_philos(t_data *data)
// {
// 	t_philo	*philos;
// 	int		i;

// 	philos = data->philos;
// 	i = 0;
// 	while (i < data->n_philos)
// 		set_state(data, &philos[i++], STOP);
// }

//	monitor each philosopher to check if one died, or all have ate enough food
void	*monitor_wellbeing(void *data_arg)
{
	t_data	*data;
	t_philo	*philos;
	int		i;
	int		n_philos;

	data = (t_data *)data_arg;
	philos = data->philos;
	n_philos = data->n_philos;
	while (get_process(data) == RUNNING)
	{
		i = 0;
		while (i < n_philos)
		{
			if (dying(data, &philos[i++]) == 1)
			{
				set_process(data, PHILO_DIED);
				pthread_mutex_lock(&data->mute_print);
				printf(RED"MONITOR: DEAD\n"NO_CLR);
				pthread_mutex_unlock(&data->mute_print);
				break ;
			}
		}
		usleep(1000);
	}
	return (NULL);
}

void	*monitor_all_full(void *data_arg)
{
	t_data	*data;
	t_philo	*philos;
	int		i;
	int		n_philos;

	data = (t_data *)data_arg;
	philos = data->philos;
	n_philos = data->n_philos;
	while (get_process(data) == RUNNING)
	{
		i = 0;
		while (i < n_philos)
		{
			if (get_satisfied(&philos[i++]) == 0)
				break ;
			set_process(data, ALL_FULL);
			pthread_mutex_lock(&data->mute_print);
			printf(BLU"MONITOR: FULL\n"NO_CLR);
			pthread_mutex_unlock(&data->mute_print);
		}
		usleep(1000);
	}
	return (NULL);
}
