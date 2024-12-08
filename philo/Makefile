# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 14:24:33 by tsomchan          #+#    #+#              #
#    Updated: 2024/12/08 20:01:47 by tsomchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	philo

SRCS_DIR			=	srcs/

# === SRCS at root of srcs/ ===
SRCS_MAIN			=	$(SRCS_DIR)main.c
SRCS_ROOT			=	thread.c \
						philosophing.c \
						time.c \
						error.c \
						free.c \
						init.c \
						parse.c \
						monitor.c \
						util.c \
						debug.c

# === SRCS in subdirectories  ===

SRCS_STATES_DIR		=	states/
SRCS_STATES			=	eating.c \
						sleeping.c


# === SRCS in debug directory  ===
SRCS_DEBUG_DIR		=	debug/


# === SRCS to compile main program  ===
SRCS				=	$(SRCS_ROOT) \
						$(addprefix $(SRCS_STATES_DIR), $(SRCS_STATES))


OBJS_DIR			=	objs/
OBJS				=	$(SRCS:%.c=$(OBJS_DIR)%.o)
OBJS_SUB_DIRS		=	$(OBJS_DIR) $(addprefix $(OBJS_DIR), $(SRCS_STATES_DIR))

HEADER_DIR			=	./includes/
HEADER 				=	philo.h color.h
HEADERS 			=	$(addprefix $(HEADER_DIR), $(HEADER))

CC 					=	cc

# === flags for compiling into object files and program. ===
CFLAGS				=	-Wall -Wextra -Werror
CFLAGS				+=	-g

FLAG_HEADERS		=	-Iincludes

# === Conditions === 
# For colorless mode
ifeq ($(COLOR_MODE), 1)
CFLAGS += -D COLOR_MODE=1
endif

#ifeq ($(T))
#endif

all : $(NAME)

$(NAME) : $(OBJS) $(SRCS_MAIN)
	$(CC) -o $(NAME) $(SRCS_MAIN) $(OBJS) -Iincludes $(CFLAGS)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c Makefile $(HEADERS) | $(OBJS_SUB_DIRS)
	$(CC) -c $< -o $@ $(FLAG_HEADERS) $(CFLAGS)

$(OBJS_SUB_DIRS):
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_SUB_DIRS)

clean :
	rm -f $(OBJS)
	rm -rf $(OBJS_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re

# === [DEBUGGING / TEST] ===

ifeq ($(V), 1)
VG_FLAG			+= --leak-check=full
VAL				= valgrind $(VG_FLAG)
endif
ifeq ($(V), 2)
VG_FLAG			+= --leak-check=full --show-leak-kinds=all
VAL				= valgrind $(VG_FLAG)
endif

#VG_FLAG			= --leak-check=full
VG_FLAG_ALL		= --leak-check=full --show-leak-kinds=all

D_NAME			=	$(addprefix d_, $(NAME))
D_FLAGS			=	-D MORE_PRINT=1

d: debug

debug: $(D_NAME)

$(D_NAME) : $(OBJS) $(SRCS_MAIN)
	$(CC) -o $(D_NAME) $(SRCS_MAIN) $(OBJS) -Iincludes $(CFLAGS) $(D_FLAGS)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c Makefile $(HEADERS) | $(OBJS_SUB_DIRS)
	$(CC) -c $< -o $@ $(FLAG_HEADERS) $(CFLAGS) $(D_FLAGS)

r: run

run: $(NAME)
	./$(NAME) $(T)

v: valgrind

valgrind: $(NAME)
	valgrind $(VG_FLAG) ./$(NAME) $(T)

va: valgrind_all

valgrind_all: $(NAME)
	valgrind $(VG_FLAG_ALL) ./$(NAME) $(T)

.PHONY: r run v valgrind va valgrind_all NO_CLR

1: $(NAME)
	$(VAL) ./$(NAME) 1 1 1 1 1

2: $(NAME)
	$(VAL) ./$(NAME) 2 2 2 2 2

5: $(NAME)
	$(VAL) ./$(NAME) 5 5 5 5 5

all_N: $(NAME)
	$(VAL) ./$(NAME) $(N) $(N) $(N) $(N) $(N)