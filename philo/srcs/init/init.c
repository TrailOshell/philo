/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:41:27 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/22 15:51:45 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forks_init(t_data *data)
{
	t_philo		*philos;
	int			i;

	philos = data->philos;
	i = 0;
	while (i < data->n_ph)
		pthread_mutex_init(&data->forks[i++], NULL);
	philos[0].fork_left = &data->forks[0];
	philos[0].fork_right = &data->forks[data->n_ph - 1];
	i = 1;
	while (i < data->n_ph)
	{
		philos[i].fork_left = &data->forks[i];
		philos[i].fork_right = &data->forks[i - 1];
		i++;
	}
	return (0);
}

int	philos_init(t_data *data)
{
	t_philo		*philos;
	int			i;

	philos = data->philos;
	i = 0;
	while (i < data->n_ph)
	{
		philos[i].id = i + 1;
		philos[i].n_eaten = 0;
		philos[i].last_meal_time = 0;
		philos[i].is_satisfied = 0;
		philos[i].state = THINKING;
		philos[i].data = data;
		pthread_mutex_init(&philos[i].mute_state, NULL);
		pthread_mutex_init(&philos[i].mute_n_eaten, NULL);
		pthread_mutex_init(&philos[i].mute_satisfied, NULL);
		pthread_mutex_init(&philos[i].mute_last_meal_time, NULL);
		i++;
	}
	return (0);
}

static void	mutex_init(t_data *data)
{
	pthread_mutex_init(&data->mute_philo, NULL);
	pthread_mutex_init(&data->mute_print, NULL);
	pthread_mutex_init(&data->mute_process, NULL);
	pthread_mutex_init(&data->mute_timestamp, NULL);
}

t_data	*data_init(t_data *data, int argc, char **argv)
{
	if (!data)
		data = malloc(sizeof(t_data));
	data->process = RUNNING;
	data->time_start = get_miliseconds();
	if (philo_parse(data, argc, argv) == 1)
	{
		free(data);
		return (NULL);
	}
	data->philos = malloc(sizeof(t_philo) * data->n_ph);
	if (data->philos == NULL)
		return (NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_ph);
	if (data->forks == NULL)
	{
		free(data->philos);
		return (NULL);
	}
	mutex_init(data);
	return (data);
}
