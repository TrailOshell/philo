/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:41:13 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/18 12:21:04 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(int ret, char *text)
{
	printf("%s", text);
	return (ret);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
		pthread_mutex_destroy(&data->forks[i++]);
	if (data->n_philos)
	{
		free(data->forks);
		free(data->philos);
		pthread_mutex_destroy(&data->mute_print);
	}
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	data = data_init(data, argc, argv);
	philos_init(data);
	forks_init(data);
	if (data == NULL)
		return (1);
	create_threads(data);
	join_threads(data);
	db_end_result(data);
	free_data(data);
	return (0);
}
