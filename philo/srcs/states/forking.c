/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:40:48 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/08 21:42:15 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	forking(t_data *data, t_philo *philo)
{
	philo->state = FORKING;
	print_timestamp(data, *philo);
	pthread_mutex_lock(philo->fork_right);
	print_timestamp(data, *philo);
	db_thread_locking(data, philo, YLW"locked"NO_CLR);
	dying(data, philo);
	return (0);
}
