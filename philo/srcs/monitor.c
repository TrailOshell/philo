/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:36:22 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/22 15:50:49 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_dead(t_data *data, t_philo *philo)
{
	if (get_state(philo) == DEAD || get_process(data) != RUNNING)
		return (0);
	pthread_mutex_lock(&data->mute_philo);
	set_process(data, PHILO_DIED);
	set_state(philo, DEAD);
	print_timestamp(data, philo->id, DEAD);
	db_mute_print(data, RED"MONITOR: DEAD\n"NO_CLR);
	pthread_mutex_unlock(&data->mute_philo);
	return (1);
}

//	set the time for the philo to die
int	momento_mori(t_data *data, t_philo *philo, unsigned long time)
{
	usleep(time);
	set_dead(data, philo);
	return (1);
}

int	dying(t_data *data, t_philo *philo)
{
	if (get_state(philo) == DEAD || get_process(data) != RUNNING)
		return (0);
	if (get_timestamp(data) - get_last_meal_time(philo)
		>= (data->t_die / 1000) + 10)
		return (set_dead(data, philo));
	return (0);
}

//	monitor each philosopher to check if one died, or all have ate enough food
void	*monitor_dying(void *data_arg)
{
	t_data	*data;
	t_philo	*philos;
	int		i;

	data = (t_data *)data_arg;
	philos = data->philos;
	i = 0;
	while (get_process(data) == RUNNING)
	{
		if (dying(data, &philos[i++]) == 1)
			break ;
		if (i == data->n_ph)
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
	i = 0;
	while (i < data->n_ph && get_process(data) == RUNNING)
	{
		if (get_satisfied(&philos[i]) == 1)
			i++;
		usleep(1000);
	}
	if (i == data->n_ph)
	{
		set_process(data, ALL_FULL);
		db_mute_print(data, BLU"MONITOR: FULL\n"NO_CLR);
	}
	return (NULL);
}
