# philo
- [x] data
	- [x] t_data
	- [x] t_philo
- [x] parsing
	- [x] no more than 5 arguments
	- [x] use ft_atoi on each argument
 - [x] "must have more than one philosopher" (no, you can still put one to die)
 - [x] "argument must be positive integers"
- [x] philosophers
	- [x] enum states (0-Idle 1-Forking 2-Eating 3-Sleeping 4-Thinking 5-Full 6-Dead)
	- [x] philosopher's number start at 1
	- [x] "Each philosopher should be a thread"
	- [x] check if they can grab forks
	- [x] ~~get full if ate enough~~ check if they've ate enough
	- [x] write function "death_by_sleep" when sleep time is more than die time
- [x] forks
	- [x] "... protect the forks state with a mutex for each of them"
- [x] timestamp
	- [x] program has data->time_start
	- [x] get_timestamp() will compare current time and data->time_start
	- [x] timestamp_in_ms X philo_state
	- [x] "A displayed state message should not be mixed up with another message"
	- [x] "... a philosopher died should be displayed no more than 10 ms after
			the actual death ..."
- [x] free
	- [x] free data when error then exit
	- [x] free data when program is done

# memory leak/error
- [x] Check thread with helgrind (from valgrind)

--------------------------------------------------------------------------------
# Makefile
- [x] basic compilation
- [x] make can input arguments (using $(T))