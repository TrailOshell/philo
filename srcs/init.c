/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:41:27 by tsomchan          #+#    #+#             */
/*   Updated: 2024/11/20 19:12:25 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	*forks_init(t_data *data)
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

t_philo	*philos_init(t_data *data)
{
	t_philo		*philos;
	int			i;

	philos = data->philos;
	i = 0;
	while (i < data->n_philos)
	{
		philos[i].id = i;
		philos[i].n_eaten = 0;
		philos[i].state = IDLE;
		i++;
	}
	return (philos);
}

t_data	*data_init(t_data *data, int argc, char **argv)
{
	if (!data)
		data = malloc(sizeof(t_data));
	data->time_start = get_miliseconds();
	philo_parse(data, argc, argv);
	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (data->philos == NULL)
		printf_and_exit(data, 1, "MALLOC ERROR");
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (data->forks == NULL)
		printf_and_exit(data, 1, "MALLOC ERROR");
	philos_init(data);
	forks_init(data);
	return (data);
}
