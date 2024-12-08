/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dying.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:41:47 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/08 21:42:19 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dying(t_data *data, t_philo *philo)
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
