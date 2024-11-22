/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:47:21 by tsomchan          #+#    #+#             */
/*   Updated: 2024/11/22 16:00:08 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	db_check_prev_next(t_philo *philo_next, t_philo *philo_prev)
{
	if (philo_next)
		printf("philo_next found: id = %d\n", philo_next->id);
	else if (!philo_next)
		printf("philo_next not found\n");
	if (philo_prev)
		printf("philo_prev found: id = %d\n", philo_prev->id);
	else if (!philo_prev)
		printf("philo_prev not found\n");

}

int	check_last_eaten(t_data *data, t_philo *philo)
{
	if (philo->last_meal_time > data->t_die)
	{
		philo->state = DEAD;
		print_timestamp(data->time_start, *philo);
		data->process_state = PHILO_DIED;
	}
	return (0);
}

int	grabbing_forks(t_data *data, t_philo *philo)
{
	t_philo	*philo_next;
	t_philo	*philo_prev;

	printf("run grabbing\n");
	philo_next = philo->next;
	philo_prev = philo->prev;
	db_check_prev_next(philo_next, philo_prev);
	if (!philo_next && !philo_prev)
	{
		printf("do nothing\n");
		check_last_eaten(data, philo);
		return (0);
	}
	if (philo_prev->state != EATING && philo_next->state != EATING)
	{
		pthread_mutex_lock(philo->fork_left);
		pthread_mutex_lock(philo->fork_right);
		philo->state = FORKING;
		print_timestamp(data->time_start, *philo);
		philo->state = EATING;
		print_timestamp(data->time_start, *philo);
		usleep(data->t_eat);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		philo->n_eaten += 1;
		if (philo->n_eaten >= data->n_philos_eat)
			philo->is_satisfied = 1;
		philo->state = SLEEPING;
		print_timestamp(data->time_start, *philo);
		usleep(data->t_sleep);
		philo->state = THINKING;
		print_timestamp(data->time_start, *philo);
	}
	return (0);
}
/*
	if (i == 0)
		philo_next = data->philos[data->n_philos];
	else
		philo_prev = data->philos[i - 1];
	if (i + 1 == data->n_philos)
		philo_next = data->philos[0];
	else
		philo_next = data->philos[i + 1];
*/

int	set_philo_state(t_data *data, t_philo *philo)
{
	printf("run 2\n");
	if (philo->state == THINKING || philo->state == FULL)
		grabbing_forks(data, philo);
	else
		check_last_eaten(data, philo);
	return (0);
}

int	check_philos_finish_must_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
		if (data->philos[i++].is_satisfied == 0)
			return (1);
	return (0);
}

int	philosophing(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		printf("run\n");
		set_philo_state(data, &data->philos[i]);
		if (data->philos[i].state == DEAD)
			break ;
		i++;
	}
	if (check_philos_finish_must_eat(data) == 0)
		data->process_state = ALL_FULL;
	return (0);
}
//printf("%d\n", i);
//printf("data->n_philos %d\n", data->n_philos);
