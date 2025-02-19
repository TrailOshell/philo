/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:42:36 by tsomchan          #+#    #+#             */
/*   Updated: 2025/02/20 01:43:21 by tsomchan         ###   ########.fr       */
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

# ifndef DEFAULT_PRINT
#  define DEFAULT_PRINT 1
# endif

# ifndef MORE_PRINT
#  define MORE_PRINT 0
# endif

# ifndef DEBUG_THREADS_LOCKING
#  define DEBUG_THREADS_LOCKING 0
# endif

// enum states for philosophers
typedef enum e_ph_state
{
	THINKING,
	FORKING,
	EATING,
	SLEEPING,
	FULL,
	DEAD,
	ALIVE
}	t_ph_state;

typedef enum e_process
{
	RUNNING,
	PHILO_DIED,
	ALL_FULL
}	t_process;

typedef struct s_philo
{
	int				id;
	int				n_eaten;
	int				is_satisfied;
	unsigned long	last_meal_time;
	struct s_data	*data;
	t_ph_state		state;
	pthread_t		thread;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	mute_state;
	pthread_mutex_t	mute_n_eaten;
	pthread_mutex_t	mute_satisfied;
	pthread_mutex_t	mute_last_meal_time;
}	t_philo;

typedef struct s_data
{
	int				n_philos;
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	int				n_philos_eat;
	unsigned long	time_start;
	int				process;
	pthread_mutex_t	mute_philo;
	pthread_mutex_t	mute_print;
	pthread_mutex_t	mute_process;
	pthread_mutex_t	mute_timestamp;
	pthread_t		alive_check;
	pthread_t		full_check;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}	t_data;

//	MAIN			=== == =
int				print_error(int ret, char *text);
void			free_data(t_data *data);

//	INIT			=== == =
t_data			*data_init(t_data *data, int argc, char **argv);
int				forks_init(t_data *data);
int				philos_init(t_data *data);

//	PARSE			=== == =
int				philo_parse(t_data *data, int argc, char **argv);

//	TIME			=== == =
unsigned long	get_miliseconds(void);
unsigned long	get_timestamp(t_data *data);
void			print_timestamp(t_data *data, int id, int state);

//	THREAD			=== == =
int				create_threads(t_data *data);
int				join_threads(t_data *data);

//	PHILOSOPHING	=== == =
void			*philosophing(void *philo_arg);

//	MONITOR			=== == =
void			*monitor_dying(void *data_arg);
void			*monitor_all_full(void *data_arg);
int				dying(t_data *data, t_philo *philo);

//	FORK
int				take_first_fork(t_philo *philo);
int				take_second_fork(t_philo *philo);
int				drop_first_fork(t_philo *philo);
int				drop_forks(t_philo *philo);

//	MUTEX_GET		=== == =
int				get_process(t_data *data);
int				get_state(t_philo *philo);
int				get_satisfied(t_philo *philo);
unsigned long	get_last_meal_time(t_philo *philo);
int				get_n_eaten(t_philo *philo);

//	MUTEX_SET		=== == =
void			set_process(t_data *data, int process);
void			set_state(t_philo *philo, int state);
void			set_satisfied(t_philo *philo, int is_satisfied);
void			set_last_meal_time(t_philo *philo, unsigned long timestamp);
void			set_n_eaten(t_philo *philo, int n_eaten);

//	UTIL			=== == =
int				ft_atoi(const char *str);
int				digit_len(unsigned long number);

//	DEBUG			=== == =
void			db_end_result(t_data *data);
void			db_thread_locking(t_data *data, t_philo *philo, char *text);
void			db_mute_print(t_data *data, char *txt);
// void			db_check_all_states(t_data *data, int id,
// 					unsigned long timestamp);

#endif
