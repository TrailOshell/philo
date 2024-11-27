/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:47:21 by tsomchan          #+#    #+#             */
/*   Updated: 2024/11/27 22:58:21 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philos_finish_must_eat(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
		if (data->philos[i++].is_satisfied == 0)
			return (1);
	return (0);
}

int	check_last_eaten(t_data *data, t_philo *philo)
{
	if (get_timestamp(data->time_start) - philo->last_meal_time > data->t_die)
	{
		philo->state = DEAD;
		print_timestamp(data->time_start, *philo);
		data->process_state = PHILO_DIED;
		db_check_all_states(data);
		return (1);
	}
	return (0);
}
	//printf(CYN "philo["B_WHT"%d"CYN"] check last eaten:"NO_CLR,
	//	philo->id);
	//printf(CYN "last meal time = "B_WHT"%lu"CYN"\t"NO_CLR,
	//	philo->last_meal_time);
	//printf(CYN "t_die = "B_WHT"%lu"CYN"\n"NO_CLR,
	//	data->t_die);

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

int	death_by_sleep(t_data *data, t_philo *philo)
{
	if (data->t_sleep >= data->t_die)
	{
		usleep(data->t_die);
		check_last_eaten(data, philo);
		return (1);
	}
	return (0);
}

int	sleeping(t_data *data, t_philo *philo)
{
	if (death_by_sleep(data, philo) == 1)
		return (0);
	usleep(data->t_sleep);
	philo->state = THINKING;
	print_timestamp(data->time_start, *philo);
	return (0);
}

int	grabbing_forks(t_data *data, t_philo *philo)
{
	t_philo	*philo_next;
	t_philo	*philo_prev;

	philo_next = philo->next;
	philo_prev = philo->prev;
	//printf(YLW "run grabbing philo["B_WHT"%d"YLW"]\t" NO_CLR,
	//	philo->id);
	//db_check_prev_next(philo_next, philo_prev);
	if (philo_prev->state != EATING && philo_next->state != EATING)
	{
		//printf(CYN "philo["B_WHT"%d"CYN"] do "YLW"something\n" NO_CLR,
		//	philo->id);
		pthread_mutex_lock(philo->fork_left);
		pthread_mutex_lock(philo->fork_right);
		db_thread_locking(philo, "locked");
		philo->state = FORKING;
		print_timestamp(data->time_start, *philo);
		philo->state = EATING;
		print_timestamp(data->time_start, *philo);
		db_check_all_states(data);
		//db_check_all_states(data);
	}
	return (0);
}

int	die_alone(t_data *data, t_philo *philo)
{
	if (data->n_philos == 1)
	{
		usleep(data->t_die);
		check_last_eaten(data, philo);
		return (1);
	}
	return (0);
}


//int	philosophing(t_data *data)
void	*philosophing(void *philo_arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_arg;
	data = philo->data;
	if (die_alone(data, philo) == 1)
		return (NULL);
	while (philo->state != DEAD && data->process_state == RUNNING)
	{
		if (philo->state == THINKING)
			grabbing_forks(data, philo);
		else if (philo->state == EATING)
			eating(data, philo);
		else if (philo->state == SLEEPING)
			sleeping(data, philo);
		//check_last_eaten(data, philo);
	}
	if (DEBUG_THREADS_DONE == 1)
		printf(YLW "thread[%d] is done\n" NO_CLR, philo->id);
	return (NULL);
}

void	*monitor_wellbeing(void *data_arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)data_arg;
	while (data->process_state == RUNNING)
	{
		i = 0;
		while (i < data->n_philos)
		{
			if (data->philos[i].state != EATING
				&& check_last_eaten(data, &data->philos[i]) == 1)
				break ;
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

//printf("%d\n", i);
//printf("data->n_philos %d\n", data->n_philos);
