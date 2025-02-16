/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 18:36:22 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/16 10:17:38 tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//	check if all philosophers have all eaten enough food
int	check_philos_all_full(t_data *data)
{
	int	i;

	i = 0;
	if (get_n_philos_eat(data) == 0)
		return (0);
	while (i < get_n_philos(data))
		if (data->philos[i++].is_satisfied == 0)
			return (0);
	set_process(data, ALL_FULL);
	return (1);
}

int	dying(t_data *data, t_philo *philo)
{
	if (get_process(data) != RUNNING)
		return (1);
	if (get_timestamp(data) - get_last_meal_time(philo)
		>= (get_t_die(data) / 1000) + 10)
	{
		set_print_state(data, philo, DEAD);
		set_process(data, PHILO_DIED);
		return (1);
	}
	return (0);
}

//	monitor each philosopher to check if one died, or all have ate enough food
void	*monitor_wellbeing(void *data_arg)
{
	t_data	*data;
	t_philo	*philos;
	int		i;
	int		n_philos;

	data = (t_data *)data_arg;
	philos = data->philos;
	n_philos = get_n_philos(data);
	while (get_process(data) == RUNNING)
	{
		i = 0;
		while (i < n_philos)
			if (dying(data, &philos[i++]) == 1)
				break ;
		check_philos_all_full(data);
		usleep(1000);
	}
	return (NULL);
}
