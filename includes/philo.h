/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:42:36 by tsomchan          #+#    #+#             */
/*   Updated: 2024/11/20 18:42:18by tsomchan         ###   ########.fr       */
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

# ifndef DEFAULT_PRINT
#  define DEFAULT_PRINT 1
# endif

# ifndef MORE_PRINT
#  define MORE_PRINT 0
# endif

# ifndef DEBUG_CREATE_THREADS
#  define DEBUG_CREATE_THREADS 0
# endif

# ifndef DEBUG_JOIN_THREADS
#  define DEBUG_JOIN_THREADS 0
# endif

# ifndef DEBUG_THREADS_LOCKING
#  define DEBUG_THREADS_LOCKING 0
# endif

# ifndef DEBUG_THREADS_DONE
#  define DEBUG_THREADS_DONE 0
# endif

// enum states for philosophers
typedef enum e_ph_state
{
	THINKING,
	FORKING,
	EATING,
	SLEEPING,
	FULL,
	DEAD
}	t_ph_state;

typedef enum e_process_state
{
	RUNNING,
	PHILO_DIED,
	ALL_FULL
}	t_process_state;

typedef struct s_philo	t_philo;

typedef struct s_philo
{
	int				id;
	int				n_eaten;
	int				is_satisfied;
	unsigned long	last_meal_time;
	t_ph_state		state;
	struct s_data	*data;
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
}	t_philo;

typedef struct s_data
{
	int				n_philos;
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	int				n_philos_eat;
	unsigned long	time_start;
	pthread_mutex_t	*forks;
	t_philo			*philos;
	pthread_mutex_t	mute_print;
	pthread_t		alive_check;
	int				process_state;
}	t_data;

//	INIT	=== == =
t_data			*data_init(t_data *data, int argc, char **argv);

//	PARSE	=== == =
int				philo_parse(t_data *data, int argc, char **argv);

//	TIME	=== == =
unsigned long	get_miliseconds(void);
unsigned long	get_timestamp(unsigned long start);
void			print_timestamp(t_data *data, t_philo philo);

//	THREAD	=== == =
void			*philosophing(void *philo_arg);
void			*monitor_wellbeing(void *data_arg);
int				check_starvation(t_data *data, t_philo *philo);
int				check_philos_finish_must_eat(t_data *data);

//	STATES	=== == =
// int				eating(t_data *data, t_philo *philo);
int				sleeping(t_data *data, t_philo *philo);

//	UTIL	=== == =
int				ft_atoi(const char *str);

//	ERROR	=== == =
void			printf_and_exit(t_data *data, int ret, char *text);

//	FREE	=== == =
void			free_data(t_data *data);

//	DEBUG	=== == =
void			db_init_philos(t_data *data);
void			db_parse_result(t_data *data);
void			db_check_prev_next(t_philo *philo_next, t_philo *philo_prev);
void			db_end_result(t_data *data);
void			db_check_all_states(t_data *data, int id);
void			db_thread_locking(t_data *data, t_philo *philo, char *text);

#endif
