/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:47:21 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/08 20:03:28 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_data *data)
{
	t_philo	*philos;
	int		i;

	pthread_create(&data->alive_check, NULL, &monitor_wellbeing, data);
	philos = data->philos;
	i = 0;
	while (i < data->n_philos)
	{
		if (DEBUG_CREATE_THREADS == 1)
			printf(PUR "create thread["B_WHT"%d"PUR"]\n" NO_CLR, i);
		if (pthread_create(&philos[i].thread, NULL, &philosophing, &philos[i]))
			return (1);
		i++;
	}
	return (0);
}

int	join_threads(t_data *data)
{
	t_philo	*philos;
	int		i;

	pthread_join(data->alive_check, NULL);
	philos = data->philos;
	i = 0;
	while (i < data->n_philos)
	{
		if (DEBUG_JOIN_THREADS == 1)
			printf(PUR "join thread["B_WHT"%d"PUR"]\n" NO_CLR, i);
		if (pthread_join(philos[i].thread, NULL))
			return (1);
		i += 2;
	}
	i = 1;
	while (i < data->n_philos)
	{
		if (DEBUG_JOIN_THREADS == 1)
			printf(PUR "join thread["B_WHT"%d"PUR"]\n" NO_CLR, i);
		if (pthread_join(philos[i].thread, NULL))
			return (1);
		i += 2;
	}
	return (0);
}
