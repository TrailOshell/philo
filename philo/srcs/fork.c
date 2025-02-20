/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:32:44 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/20 15:11:26 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_first_fork(t_data *data, t_philo *philo)
{
	if (philo->fork_left < philo->fork_right)
		pthread_mutex_lock(philo->fork_left);
	else
		pthread_mutex_lock(philo->fork_right);
	db_thread_locking(data, philo, YLW"lock first fork"NO_CLR);
	return (1);
}

int	take_second_fork(t_data *data, t_philo *philo)
{
	if (philo->fork_left < philo->fork_right)
		pthread_mutex_lock(philo->fork_right);
	else
		pthread_mutex_lock(philo->fork_left);
	db_thread_locking(data, philo, YLW"lock second fork"NO_CLR);
	return (1);
}

int	drop_first_fork(t_data *data, t_philo *philo)
{
	if (philo->fork_left < philo->fork_right)
		pthread_mutex_unlock(philo->fork_left);
	else
		pthread_mutex_unlock(philo->fork_right);
	db_thread_locking(data, philo, GRN"unlock 1 fork"NO_CLR);
	return (1);
}

int	drop_forks(t_data *data, t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	db_thread_locking(data, philo, GRN"unlock 2 forks"NO_CLR);
	return (1);
}
