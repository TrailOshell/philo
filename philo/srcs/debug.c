/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:45:54 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/16 12:37:10 by tsomchan         ###   ########.fr       */
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

	len = digit_len(get_last_meal_time(philo) / 1000);
	printf(CYN"(");
	print_empty_digit_len(get_n_philos_eat(data), philo->n_eaten);
	if (get_n_philos_eat(data) && philo->n_eaten >= get_n_philos_eat(data))
		printf(B_GRN);
	else
		printf(B_WHT);
	printf("%d "B_WHT, philo->n_eaten);
	print_empty_digit_len(die_in_ms, last_meal_time);
	if (last_meal_time >= die_in_ms + 10)
		printf(RED);
	printf("%lu"CYN")", last_meal_time);
}

void	db_check_all_states(t_data *data, int id, unsigned long timestamp)
{
	const char		*state[7] = {"🤔 ", "🍴 ", "🍝 ", "💤 ", "😃 ", "💀 "};
	char			*str;
	t_philo			*philo;
	int				i;

	if (MORE_PRINT == 0)
		return ;
	pthread_mutex_lock(&data->mute_print);
	printf(BLU "%lu\t" NO_CLR, timestamp);
	i = -1;
	while (++i < get_n_philos(data))
	{
		if (i + 1 == id)
			str = "|";
		else
			str = " ";
		printf(B_YLW "%s" NO_CLR, str);
		philo = &data->philos[i];
		printf(CYN "p"YLW"%d%s", i + 1, state[philo->state]);
		print_philo_stats(data, philo, timestamp - get_last_meal_time(philo),
			get_t_die(data) / 1000);
		printf(B_YLW "%s " NO_CLR, str);
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
	printf("%d\t", get_n_philos(data));
	printf("%lu\t", get_t_die(data) / 1000);
	printf("%lu\t", get_t_eat(data) / 1000);
	printf("%lu\t", get_t_sleep(data) / 1000);
	printf("%d", get_n_philos_eat(data));
	printf("\n"NO_CLR);
	printf("%s "BLU" end of result "NO_CLR" %s\n", deco, deco);
	printf(PUR"The philosophing has ended\n"NO_CLR);
	if (get_process(data) == ALL_FULL)
		printf(GRN"Every philosophers has philosophed philosofully🎉\n"\
			NO_CLR);
	else if (get_process(data) == PHILO_DIED)
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
		printf(CYN "threads["B_WHT"%d"CYN"] ""%s\n" NO_CLR,
			philo->id, text);
		pthread_mutex_unlock(&data->mute_print);
	}
}
