/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:41:13 by tsomchan          #+#    #+#             */
/*   Updated: 2024/11/20 19:24:55 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	db_init_philos(t_data *data)
{
	int	i;

	i = -1;
	printf(B_CYAN);
	while (++i < data->n_philos)
		printf("philos[%d]: id = %d, state = %d\n", i, data->philos[i].id, \
					data->philos[i].state);
	printf(NO_COLOR);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	data = data_init(data, argc, argv);
	db_init_philos(data);
	printf(B_CYAN"Started "B_WHITE"%lu"B_CYAN" ms ago\n"NO_COLOR, \
				get_timestamp(data->time_start));
	free_data(data);
	return (0);
}

/*
	printf("COLOR_MODE = %d\n", COLOR_MODE);
	if (COLOR_MODE == 0)
		printf(B_YELLOW "print in main\n" NO_COLOR);
	else if (COLOR_MODE == 1)
		printf("print in colorless\n");
	else
		printf("print\n");
*/