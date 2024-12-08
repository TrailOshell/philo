/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleeping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:19:21 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/08 21:57:36 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	death_by_sleep(unsigned long t_sleep, unsigned long t_die)
{
	if (t_sleep >= t_die)
	{
		usleep(t_die);
		return (1);
	}
	return (0);
}

int	sleeping(t_data *data, t_philo *philo)
{
	philo->state = SLEEPING;
	print_timestamp(data, *philo);
	if (death_by_sleep(data->t_sleep, data->t_die) == 1)
		return (1);
	micro_sleeping(data, data->t_sleep);
	if (data->process_state != RUNNING)
		return (1);
	philo->state = THINKING;
	print_timestamp(data, *philo);
	return (0);
}
