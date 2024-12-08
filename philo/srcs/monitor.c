/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:36:22 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/08 21:42:15 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philos_all_full(t_data *data)
{
	int	i;

	i = 0;
	if (data->n_philos_eat == 0)
		return (0);
	while (i < data->n_philos)
		if (data->philos[i++].is_satisfied == 0)
			return (0);
	data->process_state = ALL_FULL;
	return (1);
}

void	*monitor_wellbeing(void *data_arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_arg;
	while (data->process_state == RUNNING)
	{
		i = 0;
		while (i < data->n_philos)
		{
			if (data->philos[i].state != EATING
				&& dying(data, &data->philos[i]) == 1)
				break ;
			i++;
		}
	}
	return (NULL);
}
