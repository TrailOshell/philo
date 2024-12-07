/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:19:21 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/07 19:39:18 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_by_sleep(t_data *data, t_philo *philo)
{
	if (data->t_sleep >= data->t_die)
	{
		usleep(data->t_die);
		check_last_eaten(data, philo);
		return (1);
	}
	return (0);
}

int	sleeping(t_data *data, t_philo *philo)
{
	if (death_by_sleep(data, philo) == 1)
		return (0);
	usleep(data->t_sleep);
	philo->state = THINKING;
	print_timestamp(data, *philo);
	return (0);
}
