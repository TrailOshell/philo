/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:47:21 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/18 13:43:42 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_data *data)
{
	t_philo	*philos;
	int		i;

	if (pthread_create(&data->alive_check, NULL, &monitor_wellbeing, data))
		return (1);
	philos = data->philos;
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_create(&data->ph_threads[i], NULL,
				&philosophing, &philos[i]))
			return (1);
		i++;
	}
	return (0);
}
		// if (pthread_create(&philos[i].threads, NULL,
		// 	&philosophing, &philos[i]))

int	join_threads(t_data *data)
{
	int		i;

	if (pthread_join(data->alive_check, NULL))
		return (1);
	i = 0;
	while (i < data->n_philos)
		if (pthread_join(data->ph_threads[i++], NULL))
			return (1);
	return (0);
}
	// i = 0;
	// while (i < data->n_philos)
	// {
	// 	if (pthread_join(data->ph_threads[i], NULL))
	// 		return (1);
	// 	i += 2;
	// }
	// i = 1;
	// while (i < data->n_philos)
	// {
	// 	if (pthread_join(data->ph_threads[i], NULL))
	// 		return (1);
	// 	i += 2;
	// }
