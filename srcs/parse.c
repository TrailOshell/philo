/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:17:03 by tsomchan          #+#    #+#             */
/*   Updated: 2024/11/18 19:35:16 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// parse 

/*	according to the subject:
Your(s) program(s) should take the following arguments:
int	number_of_philosophers
int	time_to_die
int	time_to_eat
int	time_to_sleep
[number_of_times_each_philosopher_must_eat]
*/

void	db_parse_result(t_data *data)
{
	printf(B_CYAN "n_philo\tt_die\tt_eat\tt_sleep\tn_philos_eat\n" NO_COLOR);
	printf(B_WHITE "%u\t%u\t%u\t%u\t%u\n", data->n_philos, data->t_die, \
		data->t_eat, data->t_sleep, data->n_philos_eat);
}

int	philo_set_var(unsigned int *var, char *arg)
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

int	philo_parse(t_data *data, int argc, char **argv)
{
	if (argc > 6)
		printf_and_exit(1, B_RED "ERROR! Too many arguments\n" NO_COLOR);
	if (philo_set_var(&data->n_philos, argv[1]) == -1)
		printf_and_exit(1, B_RED "ERROR! Wrong number_of_philosophers\n" \
			NO_COLOR);
	if (philo_set_var(&data->t_die, argv[2]) == -1)
		printf_and_exit(1, B_RED "ERROR! Wrong time_to_die\n" NO_COLOR);
	if (philo_set_var(&data->t_eat, argv[3]) == -1)
		printf_and_exit(1, B_RED "ERROR! Wrong time_to_eat\n" NO_COLOR);
	if (philo_set_var(&data->t_sleep, argv[4]) == -1)
		printf_and_exit(1, B_RED "ERROR! Wrong time_to_sleep\n" NO_COLOR);
	if (argv[5] && philo_set_var(&data->n_philos_eat, argv[5]) == -1)
		printf_and_exit(1, B_RED "ERROR! Wrong number_of_times" \
			"_each_philosopher_must_eat\n" NO_COLOR);
	db_parse_result(data);
	return (0);
}
