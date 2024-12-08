/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:25:55 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/08 21:41:00 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	thinking(t_data *data, t_philo *philo)
{
	philo->state = THINKING;
	print_timestamp(data, *philo);
	pthread_mutex_lock(philo->fork_left);
	return (0);
}
