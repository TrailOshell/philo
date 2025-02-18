/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:32:44 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/18 13:35:14 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_first_fork(int process, t_philo *philo)
{
	if (process != RUNNING)
		return (0);
	if (philo->fork_left < philo->fork_right)
		pthread_mutex_lock(philo->fork_left);
	else
		pthread_mutex_lock(philo->fork_right);
	return (1);
}

int	take_second_fork(int process, t_philo *philo)
{
	if (process != RUNNING)
		return (0);
	if (philo->fork_left < philo->fork_right)
		pthread_mutex_lock(philo->fork_right);
	else
		pthread_mutex_lock(philo->fork_left);
	return (1);
}

void	drop_first_fork(t_philo *philo)
{
	if (philo->fork_left < philo->fork_right)
		pthread_mutex_unlock(philo->fork_left);
	else
		pthread_mutex_unlock(philo->fork_right);
}

int	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (0);
}
