/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 14:19:13 by tsomchan          #+#    #+#             */
/*   Updated: 2025/01/31 16:20:01 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ate_a_dish(t_data *data, t_philo *philo)
{
	philo->n_eaten += 1;
	if (philo->n_eaten >= data->n_philos_eat)
		philo->is_satisfied = 1;
}

static int	death_while_eat(t_data *data, t_philo *philo)
{
	unsigned long	last_meal_time;

	last_meal_time = get_timestamp(data->time_start) - philo->last_meal_time;
	// printf("meal %zu eat %zu die %zu\n", last_meal_time * 1000, t_eat, t_die);
	// printf("p%d starving for %zu\n", philo->id, philo->last_meal_time * 1000, data->t_eat, data->t_die);
	
	if (last_meal_time * 1000 + data->t_eat >= data->t_die)
	{
		// printf("p%d | meal %zu + eat %zu >= die %zu\n", philo->id, last_meal_time, data->t_eat/1000, data->t_die/1000);
		// printf(YLW"DEATH_WHILE_EAT %d\n"NO_CLR, philo->id);
		micro_sleeping(data, data->t_die - (last_meal_time * 1000));
		// printf(PUR"DEATH_WHILE_EAT %d\n"NO_CLR, philo->id);
		philo->state = DEAD;
		printf(RED"DEATH_WHILE_EAT %d\n"NO_CLR, philo->id);
		return (1);
	}
	return (0);
}

int	eating(t_data *data, t_philo *philo)
{
	philo->state = EATING;
	print_timestamp(data, *philo);
	// if (death_while_eat(data, philo) == 1)
	// {
	// 	pthread_mutex_unlock(philo->fork_left);
	// 	pthread_mutex_unlock(philo->fork_right);
	// 	db_thread_locking(data, philo, GRN"unlocked"NO_CLR);
	// }
	// else
		micro_sleeping(data, data->t_eat);
	if (data->process_state != RUNNING)
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (1);
	}
	philo->last_meal_time = get_timestamp(data->time_start);
	ate_a_dish(data, philo);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	db_thread_locking(data, philo, GRN"unlocked"NO_CLR);
	return (0);
}
