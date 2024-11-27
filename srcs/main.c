/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:41:13 by tsomchan          #+#    #+#             */
/*   Updated: 2024/11/27 22:05:32 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = data->philos;
	i = 0;
	while (i < data->n_philos)
	{
		if (DEBUG_JOIN_THREADS == 1)
			printf(PUR "join thread["B_WHT"%d"PUR"]\n" NO_CLR, i);
		if (pthread_join(philos[i].thread, NULL))
			return (1);
		i++;
	}
	pthread_join(data->alive_check, NULL);
	return (0);
}

int	create_threads(t_data *data)
{
	t_philo	*philos;
	int		i;

	philos = data->philos;
	i = 0;
	while (i < data->n_philos)
	{
		if (DEBUG_CREATE_THREADS == 1)
			printf(PUR "create thread["B_WHT"%d"PUR"]\n" NO_CLR, i);
		if (pthread_create(&philos[i].thread, NULL, &philosophing, &philos[i]))
			return (1);
		i++;
	}
	pthread_create(&data->alive_check, NULL, &monitor_wellbeing, data);
	return (0);
}

int	end_program(t_data *data)
{
	printf(PUR"The philosophing has ended\n"NO_CLR);
	if (data->process_state == ALL_FULL)
		printf(GRN"Every philosophers has philosophed philosofully🎉\n"NO_CLR);
	else if (data->process_state == PHILO_DIED)
		printf(B_WHT"A philosopher has "RED"died"B_WHT
			" from starvation💀\n"NO_CLR);
	db_end_result(data);
	free_data(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	data = data_init(data, argc, argv);
	db_init_philos(data);
	printf(B_CYN"Started "B_WHT"%lu"B_CYN" ms ago\n"NO_CLR, \
				get_timestamp(data->time_start));
	create_threads(data);
	join_threads(data);
	end_program(data);
	return (0);
}

/*
	printf("COLOR_MODE = %d\n", COLOR_MODE);
	if (COLOR_MODE == 0)
		printf(B_YLW "print in main\n" NO_CLR);
	else if (COLOR_MODE == 1)
		printf("print in colorless\n");
	else
		printf("print\n");
*/