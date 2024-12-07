/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:45:54 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/07 23:39:37 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// parse 

/*	according to the subject:
Your(s) program(s) should take the following arguments: int	number_of_philosophers
int	time_to_die
int	time_to_eat
int	time_to_sleep
[number_of_times_each_philosopher_must_eat]
*/

void	db_parse_result(t_data *data)
{
	printf(B_CYN "n_philo\tt_die\tt_eat\tt_sleep\tn_philos_eat\n" NO_CLR);
	printf(B_WHT);
	printf("%d\t", data->n_philos);
	printf("%lu\t", data->t_die / 1000);
	printf("%lu\t", data->t_eat / 1000);
	printf("%lu\t", data->t_sleep / 1000);
	printf("%d", data->n_philos_eat);
	printf("\n");
	printf(NO_CLR);
}


void	db_init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		print_timestamp(data, data->philos[i]);
	printf(B_CYN"Started "B_WHT"%lu"B_CYN" ms ago\n"NO_CLR, \
				get_timestamp(data->time_start));
}
/*
	printf(B_CYN);
	printf("philos[%d]: id = %d, state = %d\n", i, data->philos[i].id, \
				data->philos[i].state);
	printf(NO_CLR);
*/

void	db_check_prev_next(t_philo *philo_next, t_philo *philo_prev)
{
	const char		*state[7] = {"is thinking", "has taken a fork", \
						"is eating", "is sleeping", "is full", "died"};

	if (philo_prev)
		printf(PUR "philo["CYN"%d"PUR"] %s\t" NO_CLR,
			philo_prev->id, state[philo_next->state]);
	else if (!philo_prev)
		printf(PUR "philo_prev not found " NO_CLR);
	if (philo_next)
		printf(PUR "philo["CYN"%d"PUR"] %s\n" NO_CLR,
			philo_next->id, state[philo_next->state]);
	else if (!philo_next)
		printf(PUR "philo_next not found\n" NO_CLR);
	else
		printf("\n");
}

int	digit_len(int number)
{
	int	len;

	len = 0;
	while (number > 0)
	{
		number /= 10;
		len++;
	}
	return (len);
}

void	db_check_all_states(t_data *data, int id)
{
	const char		*state[7] = {"🤔 ", "🍴 ", "🍝 ", "💤 ", "😃 ", "💀 "};
	t_philo			*philo;
	int				i;
	int				len_max;
	int				len;
	unsigned long 	timestamp;
	unsigned long 	die_in_ms;
	unsigned long 	last_meal_time;


	if (MORE_PRINT == 0)
		return ;
	pthread_mutex_lock(&data->mute_print);
	timestamp = get_timestamp(data->time_start);
	die_in_ms = data->t_die / 1000;
	printf(BLU "%lu\t" NO_CLR, timestamp);
	i = -1;
	while (++i < data->n_philos)
	{
		philo = &data->philos[i];
		last_meal_time = timestamp - philo->last_meal_time;
		printf(CYN "p"YLW"%d", i + 1);
		printf("%s", state[philo->state]);
		printf(CYN"(");
		if (philo->n_eaten < 10 && data->n_philos_eat >= 10)
			printf(B_WHT" %d", philo->n_eaten);
		else
			printf(B_WHT"%d", philo->n_eaten);
		len_max = digit_len(die_in_ms);
		len = digit_len(philo->last_meal_time / 1000);
		if (philo->state != EATING && last_meal_time >= die_in_ms)
			printf(RED);
		while (len++ < len_max)
			printf(" ");
		if (philo->state != EATING)
			printf("%lu", last_meal_time);
		else
			printf("0");
		printf("/%lu", die_in_ms);
		printf(CYN")");
		if (i == id)
			printf(B_WHT"<-"NO_CLR);
		else
			printf(B_WHT"  "NO_CLR);
		printf("\t");
	}
	printf("\n");
	pthread_mutex_unlock(&data->mute_print);
}

void	db_end_result(t_data *data)
{
	const char		*deco = B_WHT"=="NO_CLR;

	if (MORE_PRINT == 0)
		return ;
	// printf("%s "BLU"start of result"NO_CLR" %s\n", deco, deco);
	db_parse_result(data);
	// db_check_all_states(data, 0);
	printf("%s "BLU" end of result "NO_CLR" %s\n", deco, deco);
}
/*
	int				i;
	i = -1;
	while (++i < data->n_philos)
	{
		philo = &data->philos[i];
		printf(CYN "philo[%d] %s (ate %d times)\n" NO_CLR,
			i, state[philo->state], philo->n_eaten);
	}
*/

void	db_thread_locking(t_data *data, t_philo *philo, char *text)
{
	int	i;

	i = 0;
	if (DEBUG_THREADS_LOCKING == 1)
	{
		pthread_mutex_lock(&data->mute_print);
		while (i++ < philo->id)
			printf("\t");
		printf(CYN "threads["B_WHT"%d"CYN"] ""%s\n" NO_CLR,
			philo->id + 1, text);
		pthread_mutex_unlock(&data->mute_print);
	}
}
