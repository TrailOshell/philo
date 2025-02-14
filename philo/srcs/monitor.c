/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:36:22 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/14 14:39:47 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	check if all philosophers have all eaten enough food
int	check_philos_all_full(t_data *data)
{
	int	i;

	i = 0;
	if (data->n_philos_eat == 0)
		return (0);
	while (i < data->n_philos)
		if (data->philos[i++].is_satisfied == 0)
			return (0);
	data->process = ALL_FULL;
	return (1);
}

int	dying(t_data *data, t_philo *philo)
{
	if (data->process != RUNNING)
		return (1);
	if (get_timestamp(data->time_start) - philo->last_meal_time
		>= (data->t_die / 1000) + 10)
	{
		philo->state = DEAD;
		print_timestamp(data, *philo);
		data->process = PHILO_DIED;
		return (1);
	}
	return (0);
}

//	monitor each philosopher to check if one died, or all have ate enough food
void	*monitor_wellbeing(void *data_arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_arg;
	while (data->process == RUNNING)
	{
		i = 0;
		while (i < data->n_philos)
			if (dying(data, &data->philos[i++]) == 1)
				break ;
		check_philos_all_full(data);
		usleep(1000);
	}
	return (NULL);
}
