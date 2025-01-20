/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:58:05 by tsomchan          #+#    #+#             */
/*   Updated: 2025/01/20 20:43:58 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	die_alone(t_data *data, t_philo *philo)
{
	if (data->n_philos == 1)
	{
		usleep(data->t_die);
		dying(data, philo);
		return (1);
	}
	return (0);
}

void	*philosophing(void *philo_arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_arg;
	data = philo->data;
	if (die_alone(data, philo) == 1)
		return (NULL);
	if (philo->id % 2 == 1)
		usleep(data->t_eat);
	while (philo->state != DEAD && data->process_state == RUNNING)
	{
		thinking(data, philo);
		if (dying(data, philo) || check_philos_all_full(data))
			break ;
		forking(data, philo);
		if (dying(data, philo) || check_philos_all_full(data))
			break ;
		eating(data, philo);
		if (dying(data, philo) || check_philos_all_full(data))
			break ;
		sleeping(data, philo);
		if (dying(data, philo) || check_philos_all_full(data))
			break ;
	}
	return (NULL);
}

/*
	if (DEBUG_THREADS_DONE == 1)
		printf(YLW "thread[%d] is done\n" NO_CLR, philo->id + 1);
*/