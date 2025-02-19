/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:17:03 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/19 14:47:25 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_set_var(int *var, char *arg)
{
	int	i;

	if (!arg)
		return (-1);
	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (-1);
		i++;
	}
	*var = ft_atoi(arg);
	if (*var <= 0)
		return (-1);
	return (0);
}

static void	init_parse(t_data *data)
{
	data->n_philos = 0;
	data->t_die = 0;
	data->t_eat = 0;
	data->t_sleep = 0;
	data->n_philos_eat = 0;
}

static void	set_parse_value(t_data *data)
{
	data->t_die *= 1000;
	data->t_eat *= 1000;
	data->t_sleep *= 1000;
}

static int	check_input(int argc)
{
	if (argc < 5)
		return (print_error(1, B_RED "ERROR! Not enough arguments\n" NO_CLR));
	if (argc > 6)
		return (print_error(1, B_RED "ERROR! Too many arguments\n" NO_CLR));
	return (0);
}

int	philo_parse(t_data *data, int argc, char **argv)
{
	init_parse(data);
	if (check_input(argc) == 1)
		return (1);
	if (philo_set_var(&data->n_philos, argv[1]) == -1)
		return (print_error(1, B_RED "ERROR! Wrong number_of_philosophers\n"\
			NO_CLR));
	if (philo_set_var((int *)&data->t_die, argv[2]) == -1)
		return (print_error(1, B_RED "ERROR! Wrong time_to_die\n" NO_CLR));
	if (philo_set_var((int *)&data->t_eat, argv[3]) == -1)
		return (print_error(1, B_RED "ERROR! Wrong time_to_eat\n" NO_CLR));
	if (philo_set_var((int *)&data->t_sleep, argv[4]) == -1)
		return (print_error(1, B_RED "ERROR! Wrong time_to_sleep\n" NO_CLR));
	if (argv[5] && philo_set_var(&data->n_philos_eat, argv[5]) == -1)
		return (print_error(1, B_RED "ERROR! Wrong number_of_times" \
			"_each_philosopher_must_eat\n" NO_CLR));
	set_parse_value(data);
	return (0);
}
