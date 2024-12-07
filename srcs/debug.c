/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:45:54 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/07 19:43:33 by tsomchan         ###   ########.fr       */
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
	printf("%lu\t", data->t_die);
	printf("%lu\t", data->t_eat);
	printf("%lu\t", data->t_sleep);
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

void	db_check_all_states(t_data *data, int id)
{
	const char		*state[7] = {"🤔 ", "🍴 ", "🍝 ", "💤 ", "😃 ", "💀 "};
	t_philo			*philo;
	int				i;

	pthread_mutex_lock(&data->mute_print);
	printf(BLU "%lu\t" NO_CLR, get_timestamp(data->time_start));
	i = -1;
	while (++i < data->n_philos)
	{
		philo = &data->philos[i];
		printf(CYN "p"YLW"%d"CYN"(", i + 1);
		if (philo->n_eaten < 10 && data->n_philos_eat >= 10)
			printf(B_WHT" %d"CYN")", philo->n_eaten);
		else
			printf(B_WHT"%d"CYN")", philo->n_eaten);
		printf("%s", state[philo->state]);
		if (i == id)
			printf(B_WHT"<-  "NO_CLR);
		else
			printf(B_WHT"    "NO_CLR);
	}
	printf("\n");
	pthread_mutex_unlock(&data->mute_print);
}

void	db_end_result(t_data *data)
{
	const char		*deco = B_WHT"=="NO_CLR;

	printf("%s "BLU"start of result"NO_CLR" %s\n", deco, deco);
	db_parse_result(data);
	db_check_all_states(data, 0);
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

void	db_thread_locking(t_philo *philo, char *text)
{
	if (DEBUG_THREADS_LOCKING == 1)
	{
		printf(CYN "threads["B_WHT"%d"CYN"] %s\n" NO_CLR,
			philo->id + 1, text);
	}
}
