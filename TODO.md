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
	- [ ] catch overflow?
- [ ] thread
- [ ] philosophers
	- [ ] enum states (0-Idle 1-Eating 2-Sleeping 3-Thinking 4-Full 5-Dead)
	- [ ] check if they can grab forks
	- [ ] get full if ate enough
- [ ] timestamp
	- [ ] timestamp_in_ms X philo_state
- [ ] free
	- [ ] free data

## color
- [ ] COLOR_MODE (0 has color, 1 no color)

--------------------------------------------------------------------------------
# Makefile
- [x] basic compilation
- [x] make can input arguments (using $(T))
- [ ] loading bar?