/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:36:22 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/08 20:00:00 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philos_finish_must_eat(t_data *data)
{
	int	i;

	i = 0;
	if (data->n_philos_eat == 0)
		return (1);
	while (i < data->n_philos)
		if (data->philos[i++].is_satisfied == 0)
			return (1);
	return (0);
}

int	check_starvation(t_data *data, t_philo *philo)
{
	if (get_timestamp(data->time_start) - philo->last_meal_time
		>= data->t_die / 1000)
	{
		philo->state = DEAD;
		print_timestamp(data, *philo);
		data->process_state = PHILO_DIED;
		return (1);
	}
	return (0);
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
				&& check_starvation(data, &data->philos[i]) == 1)
				break ;
			i++;
		}
	}
	return (NULL);
}
