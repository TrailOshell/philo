/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:41:27 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/16 10:47:10 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	*forks_init(t_data *data)
{
	t_philo		*philos;
	int			i;

	philos = data->philos;
	i = 0;
	while (i < data->n_philos)
		pthread_mutex_init(&data->forks[i++], NULL);
	philos[0].fork_left = &data->forks[0];
	philos[0].fork_right = &data->forks[data->n_philos - 1];
	i = 1;
	while (i < data->n_philos)
	{
		philos[i].fork_left = &data->forks[i];
		philos[i].fork_right = &data->forks[i - 1];
		i++;
	}
	return (0);
}

static t_philo	*philos_init(t_data *data)
{
	t_philo		*philos;
	int			i;

	philos = data->philos;
	i = 0;
	while (i < data->n_philos)
	{
		philos[i].id = i + 1;
		philos[i].n_eaten = 0;
		philos[i].last_meal_time = 0;
		philos[i].is_satisfied = 0;
		philos[i].state = THINKING;
		philos[i].data = data;
		pthread_mutex_init(&philos[i].mute_state, NULL);
		pthread_mutex_init(&philos[i].mute_satisfied, NULL);
		pthread_mutex_init(&philos[i].mute_last_meal_time, NULL);
		i++;
	}
	return (philos);
}

t_data	*data_init(t_data *data, int argc, char **argv)
{
	if (!data)
		data = malloc(sizeof(t_data));
	data->process = RUNNING;
	data->time_start = get_miliseconds();
	philo_parse(data, argc, argv);
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (data->philos == NULL)
	{
		print_error(1, "MALLOC ERROR");
		return (NULL);
	}
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (data->forks == NULL)
	{
		print_error(1, "MALLOC ERROR");
		return (NULL);
	}
	pthread_mutex_init(&data->mute_print, NULL);
	pthread_mutex_init(&data->mute_process, NULL);
	philos_init(data);
	forks_init(data);
	return (data);
}
