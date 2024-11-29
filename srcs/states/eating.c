/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:19:13 by tsomchan          #+#    #+#             */
/*   Updated: 2024/11/29 14:25:45 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_data *data, t_philo *philo)
{
	printf(YLW "thread[%d] is eating\n" NO_CLR, philo->id);
	usleep(data->t_eat);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	db_thread_locking(philo, "unlocked");
	philo->last_meal_time = get_timestamp(data->time_start);
	philo->state = SLEEPING;
	print_timestamp(data->time_start, *philo);
	philo->n_eaten += 1;
	if (philo->n_eaten >= data->n_philos_eat)
		philo->is_satisfied = 1;
	if (check_philos_finish_must_eat(data) == 0)
		data->process_state = ALL_FULL;
	return (0);
}
