/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:45:54 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/08 17:42:35 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_empty_digit_len(int digit_max, int digit)
{
	int				len_max;
	int				len;

	len_max = digit_len(digit_max);
	len = digit_len(digit);
	while (len++ < len_max)
		printf(" ");
}

static void	print_philo_stats(t_data *data, t_philo *philo,
			unsigned long last_meal_time, unsigned long die_in_ms)
{
	printf(CYN"(");
	print_empty_digit_len(data->n_philos_eat, philo->n_eaten);
	printf(B_WHT"%d", philo->n_eaten);
	if (philo->state != EATING && last_meal_time >= die_in_ms)
		printf(RED);
	print_empty_digit_len(die_in_ms, philo->last_meal_time / 1000);
	if (philo->state == EATING)
		last_meal_time = 0;
	printf("%lu/%lu"CYN")", last_meal_time, die_in_ms);
}

void	db_check_all_states(t_data *data, int id, unsigned long timestamp)
{
	const char		*state[7] = {"🤔 ", "🍴 ", "🍝 ", "💤 ", "😃 ", "💀 "};
	t_philo			*philo;
	int				i;

	if (MORE_PRINT == 0)
		return ;
	pthread_mutex_lock(&data->mute_print);
	printf(BLU "%lu\t" NO_CLR, timestamp);
	i = -1;
	while (++i < data->n_philos)
	{
		philo = &data->philos[i];
		printf(CYN "p"YLW"%d%s", i + 1, state[philo->state]);
		print_philo_stats(data, philo, timestamp - philo->last_meal_time,
			data->t_die / 1000);
		if (i == id)
			printf(B_WHT"<-\t"NO_CLR);
		else
			printf(B_WHT"  \t"NO_CLR);
	}
	printf("\n");
	pthread_mutex_unlock(&data->mute_print);
}

void	db_end_result(t_data *data)
{
	const char		*deco = B_WHT"=="NO_CLR;

	if (MORE_PRINT == 0)
		return ;
	printf(B_CYN "n_philo\tt_die\tt_eat\tt_sleep\tn_philos_eat\n" NO_CLR);
	printf(B_WHT);
	printf("%d\t", data->n_philos);
	printf("%lu\t", data->t_die / 1000);
	printf("%lu\t", data->t_eat / 1000);
	printf("%lu\t", data->t_sleep / 1000);
	printf("%d", data->n_philos_eat);
	printf("\n");
	printf(NO_CLR);
	printf("%s "BLU" end of result "NO_CLR" %s\n", deco, deco);
}

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

/*
void	db_init_philos(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philos)
		print_timestamp(data, data->philos[i]);
	printf(B_CYN"Started "B_WHT"%lu"B_CYN" ms ago\n"NO_CLR, \
				get_timestamp(data->time_start));
}
*/