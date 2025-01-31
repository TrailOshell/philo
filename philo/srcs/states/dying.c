/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dying.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:41:47 by tsomchan          #+#    #+#             */
/*   Updated: 2025/01/31 16:37:21 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dying(t_data *data, t_philo *philo)
{
	if (data->process_state != RUNNING)
		return (1);
	if (get_timestamp(data->time_start) - philo->last_meal_time
		>= data->t_die / 1000)
	{
		philo->state = DEAD;
		print_timestamp(data, *philo);
		data->process_state = PHILO_DIED;
		printf(RED"DYING %d\n"NO_CLR, philo->id);
		return (1);
	}
	return (0);
}
