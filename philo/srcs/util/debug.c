/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:45:54 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/20 18:06:19 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	db_end_result(t_data *data)
{
	const char		*deco = B_WHT"=="NO_CLR;
	const char		*deco1 = B_WHT"<=="NO_CLR;
	const char		*deco2 = B_WHT"==>"NO_CLR;

	if (DEBUG_PRINT == 0)
		return ;
	printf(B_CYN "n_philo\tt_die\tt_eat\tt_sleep\tn_philos_eat\n" NO_CLR);
	printf(B_WHT);
	printf("%d\t", data->n_ph);
	printf("%lu\t", data->t_die / 1000);
	printf("%lu\t", data->t_eat / 1000);
	printf("%lu\t", data->t_sleep / 1000);
	printf("%d", data->n_ph_eat);
	printf("\n"NO_CLR);
	printf("%s "PUR" The philosophing has ended "NO_CLR" %s\n", deco1, deco2);
	if (get_process(data) == ALL_FULL)
		printf(GRN"Every philosophers has philosophed philosofully🎉\n"\
			NO_CLR);
	else if (get_process(data) == PHILO_DIED)
		printf(B_WHT"A philosopher has "RED"died"B_WHT
			" from starvation💀\n"NO_CLR);
}

void	db_mute_print(t_data *data, char *txt)
{
	if (DEBUG_PRINT == 0)
		return ;
	pthread_mutex_lock(&data->mute_print);
	printf("%s", txt);
	pthread_mutex_unlock(&data->mute_print);
}

void	db_thread_locking(t_data *data, t_philo *philo, char *text)
{
	if (DEBUG_THREADS_LOCKING == 0)
		return ;
	pthread_mutex_lock(&data->mute_print);
	printf(CYN "threads["B_WHT"%d"CYN"] ""%s\n" NO_CLR,
		philo->id, text);
	pthread_mutex_unlock(&data->mute_print);
}
