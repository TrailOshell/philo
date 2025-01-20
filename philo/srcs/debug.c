/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:45:54 by tsomchan          #+#    #+#             */
/*   Updated: 2025/01/20 21:56:26 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	print_empty_digit_len(int digit_max, int digit)
static void	print_empty_digit_len(unsigned long digit_max, unsigned long digit)
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
	int	len;

	len = digit_len(philo->last_meal_time / 1000);
	printf(CYN"(");
	print_empty_digit_len(data->n_philos_eat, philo->n_eaten);
	printf(B_WHT"%d ", philo->n_eaten);
	// print_empty_digit_len(die_in_ms, philo->last_meal_time / 1000);
	print_empty_digit_len(die_in_ms, last_meal_time);
	if (last_meal_time >= die_in_ms)
		printf(RED);
	printf("%lu"CYN")", last_meal_time);
}
/*
	if (philo->state != EATING && last_meal_time >= die_in_ms)
		printf(RED);
	printf("%lu/%lu"CYN")", last_meal_time, die_in_ms);
*/

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
			printf(B_WHT"<- "NO_CLR);
		else
			printf(B_WHT"   "NO_CLR);
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
	printf("\n"NO_CLR);
	printf("%s "BLU" end of result "NO_CLR" %s\n", deco, deco);
	printf(PUR"The philosophing has ended\n"NO_CLR);
	if (data->process_state == ALL_FULL)
		printf(GRN"Every philosophers has philosophed philosofully🎉\n"\
			NO_CLR);
	else if (data->process_state == PHILO_DIED)
		printf(B_WHT"A philosopher has "RED"died"B_WHT
			" from starvation💀\n"NO_CLR);
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
