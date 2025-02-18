# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsomchan <tsomchan@student.42bangkok.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 14:24:33 by tsomchan          #+#    #+#              #
#    Updated: 2025/02/18 14:59:53 by tsomchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	philo

SRCS_DIR			=	srcs/

# === SRCS at root of srcs/ ===
SRCS_MAIN			=	$(SRCS_DIR)main.c
SRCS_ROOT			=	philosophing.c \
						time.c \
						monitor.c \
						fork.c \
						mutex_get.c mutex_set.c\
						util.c \
						debug.c

# === SRCS in subdirectories  ===
SRCS_INIT_DIR		=	init/
SRCS_INIT			=	init.c \
						parse.c \
						thread.c

# === SRCS to compile main program  ===
SRCS				=	$(SRCS_ROOT) \
						$(addprefix $(SRCS_INIT_DIR), $(SRCS_INIT))

OBJS_DIR			=	objs/
OBJS				=	$(SRCS:%.c=$(OBJS_DIR)%.o)
OBJS_SUB_DIRS		=	$(OBJS_DIR) $(addprefix $(OBJS_DIR), $(SRCS_INIT_DIR))

D_OBJS				=	$(SRCS:%.c=$(OBJS_DIR)%_d.o)

HEADER_DIR			=	./includes/
HEADER 				=	philo.h color.h
HEADERS 			=	$(addprefix $(HEADER_DIR), $(HEADER))

CC 					=	cc

# === flags for compiling into object files and program. ===
C_FLAGS				=	-Wall -Wextra -Werror -g

FLAG_HEADERS		=	-Iincludes

all : $(NAME) $(D_NAME)

$(NAME) : $(OBJS) $(SRCS_MAIN)
	$(CC) -o $(NAME) $(SRCS_MAIN) $(OBJS) -Iincludes $(C_FLAGS)

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

# D_FLAGS		=	-g -D DEFAULT_PRINT=0 -D MORE_PRINT=1
D_FLAGS		=	-g -D DEFAULT_PRINT=1 -D MORE_PRINT=0

d: debug 

debug: $(D_NAME)

$(D_NAME) : $(D_OBJS) $(SRCS_MAIN)
	$(CC) -o $(D_NAME) $(SRCS_MAIN) $(D_OBJS) -Iincludes $(CFLAGS) $(D_FLAGS)

$(OBJS_DIR)%_d.o : $(SRCS_DIR)%.c Makefile $(HEADERS) | $(OBJS_SUB_DIRS)
	$(CC) -c $< -o $@ $(FLAG_HEADERS) $(CFLAGS) $(D_FLAGS)

.PHONY: d debug

v: valgrind

valgrind: $(NAME)
	valgrind $(VG_FLAG) ./$(NAME) 2 900000 20 20 1

va: valgrind_all

valgrind_all: $(NAME)
	valgrind $(VG_FLAG_ALL) ./$(NAME)

.PHONY: v valgrind va valgrind_all