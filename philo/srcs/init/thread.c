/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:47:21 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/20 18:06:19 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_data *data)
{
	t_philo	*philos;
	int		i;

	if (pthread_create(&data->alive_check, NULL, &monitor_dying, data))
		return (1);
	if (data->n_ph_eat)
		if (pthread_create(&data->full_check, NULL, &monitor_all_full, data))
			return (1);
	philos = data->philos;
	i = 0;
	while (i < data->n_ph)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				&philosophing, &philos[i]))
			return (1);
		i++;
	}
	return (0);
}

int	join_threads(t_data *data)
{
	int		i;

	if (pthread_join(data->alive_check, NULL))
		return (1);
	if (pthread_join(data->full_check, NULL))
		return (1);
	i = 0;
	while (i < data->n_ph)
		if (pthread_join(data->philos[i++].thread, NULL))
			return (1);
	return (0);
}
