/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:41:13 by tsomchan          #+#    #+#             */
/*   Updated: 2024/12/07 23:40:47 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_threads(t_data *data)
{
	t_philo	*philos;
	int		i;

	pthread_join(data->alive_check, NULL);
	philos = data->philos;
	i = 0;
	while (i < data->n_philos)
	{
		if (DEBUG_JOIN_THREADS == 1)
			printf(PUR "join thread["B_WHT"%d"PUR"]\n" NO_CLR, i);
		if (pthread_join(philos[i].thread, NULL))
			return (1);
		i += 2;
	}
	i = 1;
	while (i < data->n_philos)
	{
		if (DEBUG_JOIN_THREADS == 1)
			printf(PUR "join thread["B_WHT"%d"PUR"]\n" NO_CLR, i);
		if (pthread_join(philos[i].thread, NULL))
			return (1);
		i += 2;
	}
	return (0);
}

int	create_threads(t_data *data)
{
	t_philo	*philos;
	int		i;

	pthread_create(&data->alive_check, NULL, &monitor_wellbeing, data);
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
	return (0);
}

int	end_program(t_data *data)
{
	if (MORE_PRINT == 1)
	{
		printf(PUR"The philosophing has ended\n"NO_CLR);
		if (data->process_state == ALL_FULL)
			printf(GRN"Every philosophers has philosophed philosofully🎉\n"\
				NO_CLR);
		else if (data->process_state == PHILO_DIED)
			printf(B_WHT"A philosopher has "RED"died"B_WHT
				" from starvation💀\n"NO_CLR);
		db_end_result(data);
	}
	free_data(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	data = data_init(data, argc, argv);
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