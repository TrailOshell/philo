/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:19:13 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/08 20:08:56 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ate_a_dish(t_data *data, t_philo *philo)
{
	philo->n_eaten += 1;
	if (philo->n_eaten >= data->n_philos_eat)
		philo->is_satisfied = 1;
	if (check_philos_finish_must_eat(data) == 0)
		data->process_state = ALL_FULL;
}

int	eating(t_data *data, t_philo *philo)
{
	print_timestamp(data, *philo);
	usleep(data->t_eat);
	philo->last_meal_time = get_timestamp(data->time_start);
	ate_a_dish(data, philo);
	return (0);
}
