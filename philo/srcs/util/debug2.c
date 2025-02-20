/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:22:23 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/20 15:07:58 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_empty_digit_len(unsigned long digit_max,
	unsigned long digit)
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
	const char		*txt[7] = {WHT, WHT, YLW, BLU, GRN, RED};
	int				len;
	int				n_eaten;

	len = digit_len(get_last_meal_time(philo) / 1000);
	n_eaten = get_n_eaten(philo);
	printf(CYN"(");
	print_empty_digit_len(data->n_philos_eat, n_eaten);
	if (data->n_philos_eat && n_eaten >= data->n_philos_eat)
		printf(B_GRN);
	else
		printf(B_YLW);
	printf("%d "B_WHT, n_eaten);
	print_empty_digit_len(die_in_ms, last_meal_time);
	if (last_meal_time >= die_in_ms + 10)
		printf(RED);
	else
		printf("%s", txt[get_state(philo)]);
	printf("%lu"CYN")", last_meal_time);
}

void	db_check_all_ph(t_data *data, int id, unsigned long timestamp)
{
	const char		*txt[7] = {"🤔 ", "🍴 ", "🍝 ", "💤 ", "😃 ", "💀 "};
	char			*str;
	t_philo			*philo;
	int				i;

	if (DEBUG_PRINT == 0)
		return ;
	printf(BLU "%lu\t" NO_CLR, timestamp);
	i = -1;
	while (++i < data->n_philos)
	{
		if (i + 1 == id)
			str = "||";
		else
			str = "  ";
		printf(B_YLW "%s" NO_CLR, str);
		philo = &data->philos[i];
		printf(CYN "p"YLW"%d%s", i + 1, txt[get_state(&data->philos[i])]);
		print_philo_stats(data, philo, timestamp - get_last_meal_time(philo),
			data->t_die / 1000);
		printf(B_YLW "%s " NO_CLR, str);
	}
	printf("\n");
}
