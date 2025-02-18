/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:37:00 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/18 13:58:06 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_state(t_philo *philo)
{
	int	state;

	pthread_mutex_lock(&philo->mute_state);
	state = philo->state;
	pthread_mutex_unlock(&philo->mute_state);
	return (state);
}

void	set_state(t_data *data, t_philo *philo, int state)
{
	pthread_mutex_lock(&philo->mute_state);
	philo->state = state;
	pthread_mutex_unlock(&philo->mute_state);
}

int	get_process(t_data *data)
{
	int	process;

	pthread_mutex_lock(&data->mute_process);
	process = data->process;
	pthread_mutex_unlock(&data->mute_process);
	return (process);
}

void	set_process(t_data *data, int process)
{
	pthread_mutex_lock(&data->mute_process);
	data->process = process;
	pthread_mutex_unlock(&data->mute_process);
}

int	get_n_eaten(t_philo *philo)
{
	int	n_eaten;

	pthread_mutex_lock(&philo->mute_n_eaten);
	n_eaten = philo->n_eaten;
	pthread_mutex_unlock(&philo->mute_n_eaten);
	return (n_eaten);
}

int	set_n_eaten(t_philo *philo, int	n_eaten)
{
	pthread_mutex_lock(&philo->mute_n_eaten);
	philo->n_eaten = n_eaten;
	pthread_mutex_unlock(&philo->mute_n_eaten);
}

int	get_satisfied(t_philo *philo)
{
	int	is_satisfied;

	pthread_mutex_lock(&philo->mute_satisfied);
	is_satisfied = philo->is_satisfied;
	pthread_mutex_unlock(&philo->mute_satisfied);
	return (is_satisfied);
}

void	set_satisfied(t_philo *philo, int is_satisfied)
{
	pthread_mutex_lock(&philo->mute_satisfied);
	philo->is_satisfied = is_satisfied;
	pthread_mutex_unlock(&philo->mute_satisfied);
}

unsigned long 	get_last_meal_time(t_philo *philo)
{
	unsigned long	meal_time;

	pthread_mutex_lock(&philo->mute_last_meal_time);
	meal_time = philo->last_meal_time;
	pthread_mutex_unlock(&philo->mute_last_meal_time);
	return (meal_time);
}

void	set_last_meal_time(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->mute_last_meal_time);
	philo->last_meal_time = get_timestamp(data);
	pthread_mutex_unlock(&philo->mute_last_meal_time);
}

//unsigned long	get_t_die(t_data *data)
//{
//	unsigned long	t_die;

//	pthread_mutex_lock(&data->mute_t_die);
//	t_die = data->t_die;
//	pthread_mutex_unlock(&data->mute_t_die);
//	return (t_die);
//}

//unsigned long	get_t_eat(t_data *data)
//{
//	unsigned long	t_eat;

//	pthread_mutex_lock(&data->mute_t_eat);
//	t_eat = data->t_eat;
//	pthread_mutex_unlock(&data->mute_t_eat);
//	return (t_eat);
//}

//unsigned long	get_t_sleep(t_data *data)
//{
//	unsigned long	t_sleep;

//	pthread_mutex_lock(&data->mute_t_sleep);
//	t_sleep = data->t_sleep;
//	pthread_mutex_unlock(&data->mute_t_sleep);
//	return (t_sleep);
//}

//int	get_n_philos(t_data *data)
//{
//	unsigned long	n_philos;

//	pthread_mutex_lock(&data->mute_n_philos);
//	n_philos = data->n_philos;
//	pthread_mutex_unlock(&data->mute_n_philos);
//	return (n_philos);
//}

//int	get_n_philos_eat(t_data *data)
//{
//	unsigned long	n_philos_eat;

//	pthread_mutex_lock(&data->mute_n_philos_eat);
//	n_philos_eat = data->n_philos_eat;
//	pthread_mutex_unlock(&data->mute_n_philos_eat);
//	return (n_philos_eat);
//}
