/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:42:36 by tsomchan          #+#    #+#             */
/*   Updated: 2024/11/20 18:03:27 by tsomchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "color.h"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# ifndef COLOR_MODE
#  define COLOR_MODE 0
# endif


typedef struct s_data
{
	unsigned int	n_philos;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	n_philos_eat;
	unsigned long	time_start;
}	t_data;

//	INIT	=== == =
t_data			*philo_init(t_data *data, int argc, char **argv);

//	PARSE	=== == =
int				philo_parse(t_data *data, int argc, char **argv);

//	TIME	=== == =
unsigned long	get_miliseconds(void);
unsigned long	get_timestamp(unsigned long start);

//	UTIL	=== == =
int				ft_atoi(const char *str);

//	ERROR	=== == =
void			printf_and_exit(t_data *data, int ret, char *text);

//	FREE	=== == =
void			free_data(t_data *data);

#endif
