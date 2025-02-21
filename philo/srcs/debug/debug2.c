/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:22:23 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/22 00:40:41 by tsomchan         ###   ########.fr       */
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
	const char		*state[7] = {"🤔", "🍴", "🍝", "💤", "😃", "💀"};
	const char		*txt[7] = {WHT, WHT, YLW, BLU, GRN, RED};
	char			*color;
	int				i;
	int				n_eaten;

	i = philo->id - 1;
	printf(CYN "p"YLW"%d%s", i + 1, state[get_state(&data->philos[i])]);
	n_eaten = get_n_eaten(philo);
	if (get_process(data) == RUNNING)
		color = CYN;
	else
		color = RED;
	printf("%s(", color);
	print_empty_digit_len(data->n_ph_eat, n_eaten);
	if (data->n_ph_eat && n_eaten >= data->n_ph_eat)
		printf(B_GRN);
	else
		printf(B_YLW);
	printf("%d🍽️  "B_WHT, n_eaten);
	print_empty_digit_len(die_in_ms, last_meal_time);
	if (last_meal_time >= die_in_ms + 10)
		printf(RED);
	printf("%s", txt[get_state(philo)]);
	printf("%lu⏳%s)", last_meal_time, color);
}

void	db_check_all_ph_ex(void)
{
	const char	*state[7] = {"🤔 ", "🍴 ", "🍝 ", "💤 ", "😃 ", "💀 "};
	const char	*symbol = YLW"||"NO_CLR;

	printf("\n");
	printf(PUR"     v %s"PUR"the philo that print this timestamp%s"PUR" v"
		NO_CLR, symbol, symbol);
	printf(PUR"     v other philo v"NO_CLR);
	printf("\n");
	printf(CYN"XXms      "NO_CLR);
	printf(YLW"||"NO_CLR);
	printf(CYN"p" YLW"1" "%s", state[0]);
	printf(CYN"(" YLW"n_eaten🍽️ " WHT" last"YLW"_meal_"BLU"time⏳" CYN")");
	printf(YLW"||"NO_CLR);
	printf("        ");
	printf(CYN"p" YLW"2" "%s" CYN"(" GRN"full🍽️ " RED" dead⏳" CYN")", state[0]);
	printf(CYN"      XXms\n"NO_CLR"(");
	printf("%s"WHT"is thinking ", state[0]);
	printf("%s"WHT"has taken a fork ", state[1]);
	printf("%s"YLW"is eating ", state[2]);
	printf("%s"BLU"is sleeping ", state[3]);
	printf("%s"RED"died", state[5]);
	printf(NO_CLR")\n");
}

void	db_check_all_ph(t_data *data, int id, unsigned long timestamp)
{
	char			*str;
	t_philo			*philo;
	int				i;

	if (DB_PRINT == 0)
		return ;
	printf(CYN "%lu\t" NO_CLR, timestamp);
	i = -1;
	while (++i < data->n_ph)
	{
		if (i + 1 == id)
			str = "||";
		else
			str = "  ";
		printf(B_YLW "%s" NO_CLR, str);
		philo = &data->philos[i];
		if (timestamp < get_last_meal_time(philo))
			print_philo_stats(data, philo, 0, data->t_die / 1000);
		else
			print_philo_stats(data, philo,
				timestamp - get_last_meal_time(philo), data->t_die / 1000);
		printf(B_YLW "%s " NO_CLR, str);
	}
	printf(CYN "    %lu"NO_CLR "\n", timestamp);
}
