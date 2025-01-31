/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:58:05 by tsomchan          #+#    #+#             */
/*   Updated: 2025/01/31 16:28:21 by tsomchan         ###   ########.fr       */
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
	if (philo->id % 2 == 0)
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
		// printf(GRN"ATE\n"NO_CLR);
		if (dying(data, philo) || check_philos_all_full(data))
		// {
		// 	printf(PUR"BREAK EATING\n"NO_CLR);
			break ;
		// }
		sleeping(data, philo);
		// printf(GRN"SLEPT\n"NO_CLR);
		if (dying(data, philo) || check_philos_all_full(data))
		// {
		// 	printf(PUR"BREAK SLEEPING\n"NO_CLR);
			break ;
		// }
	}
	return (NULL);
}

/*
	if (DEBUG_THREADS_DONE == 1)
		printf(YLW "thread[%d] is done\n" NO_CLR, philo->id + 1);
*/