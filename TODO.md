# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    TODO.md                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 19:43:24 by tsomchan          #+#    #+#              #
#    Updated: 2024/11/18 19:43:28 by tsomchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# philo
- [ ] data
	- [ ] t_data
	- [ ] t_philo
- [ ] parsing
	- [x] no more than 5 arguments
	- [x] use ft_atoi on each argument
 - [x] "must have more than one philosopher" (no, you can still put one to die)
 - [ ] "argument must be positive integers"
	- [ ] catch overflow?
- [ ] philosophers
	- [x] enum states (0-Idle 1-Forking 2-Eating 3-Sleeping 4-Thinking 5-Full 6-Dead)
	- [ ] philosopher's number start at 1
	- [x] "Each philosopher should be a thread"
	- [ ] check if they can grab forks
	- [ ] get full if ate enough
	- [ ] write function "death_by_sleep" when sleep time is more than die time
- [ ] forks
	- [ ] "... protect the forks state with a mutex for each of them"
	- [ ] enum states (0-Idle 1-Taken)
- [ ] timestamp
	- [x] program has data->time_start
	- [x] get_timestamp() will compare current time and data->time_start
	- [x] timestamp_in_ms X philo_state
	- [ ] "A displayed state message should not be mixed up with another message"
	- [ ] "... a philosopher died should be displayed no more than 10 ms after
			the actual death ..."
- [ ] free
	- [ ] free data when error then exit
	- [ ] free data when program is done

## color
- [ ] COLOR_MODE (0 has color, 1 no color)

--------------------------------------------------------------------------------
# Makefile
- [x] basic compilation
- [x] make can input arguments (using $(T))
- [ ] loading bar?