# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsomchan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 14:24:33 by tsomchan          #+#    #+#              #
#    Updated: 2025/02/21 02:28:53 by tsomchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	philo

SRCS_DIR			=	srcs/

# === SRCS at root of srcs/ ===
SRCS_MAIN			=	$(SRCS_DIR)main.c
SRCS_ROOT			=	philosophing.c \
						monitor.c \
						time.c \
						fork.c \

# === SRCS in subdirectories  ===
SRCS_INIT_DIR		=	init/
SRCS_INIT			=	init.c \
						parse.c \
						thread.c

SRCS_UTIL_DIR		=	util/
SRCS_UTIL			=	util.c \
						mutex_get.c mutex_set.c\
						debug.c debug2.c

# === SRCS to compile main program  ===
SRCS				=	$(SRCS_ROOT) \
						$(addprefix $(SRCS_INIT_DIR), $(SRCS_INIT)) \
						$(addprefix $(SRCS_UTIL_DIR), $(SRCS_UTIL))

OBJS_DIR			=	objs/
OBJS				=	$(SRCS:%.c=$(OBJS_DIR)%.o)
OBJS_SUB_DIRS		=	$(OBJS_DIR) $(addprefix $(OBJS_DIR), $(SRCS_INIT_DIR) $(SRCS_UTIL_DIR))

D_OBJS				=	$(SRCS:%.c=$(OBJS_DIR)%_d.o)

HEADER_DIR			=	./includes/
HEADER 				=	philo.h color.h
HEADERS 			=	$(addprefix $(HEADER_DIR), $(HEADER))

CC 					=	cc

# === flags for compiling into object files and program. ===
C_FLAGS				=	-Wall -Wextra -Werror

FLAG_HEADERS		=	-Iincludes

all : $(NAME) $(D_NAME) run

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
	rm -f $(TXT) $(D_TXT)

re : fclean all

.PHONY : all clean fclean re

# === [DEBUG PROGRAM] ===

D_NAME		=	$(addprefix d_, $(NAME))
D_FLAGS		=	-g -D DEFAULT_PRINT=0 -D DB_PRINT=1

TXT			=	philo.txt
D_TXT		=	d_philo.txt

d: debug 

debug: $(D_NAME) d_run

$(D_NAME) : $(D_OBJS) $(SRCS_MAIN)
	$(CC) -o $(D_NAME) $(SRCS_MAIN) $(D_OBJS) -Iincludes $(CFLAGS) $(D_FLAGS)

$(OBJS_DIR)%_d.o : $(SRCS_DIR)%.c Makefile $(HEADERS) | $(OBJS_SUB_DIRS)
	$(CC) -c $< -o $@ $(FLAG_HEADERS) $(CFLAGS) $(D_FLAGS)

.PHONY: d debug

run:
ifdef T
	./$(NAME) $(T) > $(TXT)
	cat $(TXT)
else
endif

d_run:
ifdef T
	./$(D_NAME) $(T) > $(D_TXT)
	cat $(D_TXT)
else
endif

# === [VALGRIND] ===

ifeq ($(V), 1)
VG_FLAG			+= --leak-check=full
VAL				= valgrind $(VG_FLAG)
endif
ifeq ($(V), 2)
VG_FLAG			+= --leak-check=full --show-leak-kinds=all
VAL				= valgrind $(VG_FLAG)
endif

VG_FLAG			= --leak-check=full
VG_FLAG_ALL		= --leak-check=full --show-leak-kinds=all

v: valgrind
valgrind: $(NAME)
	valgrind $(VG_FLAG) ./$(NAME) 2 900000 60 60 1

va: valgrind_all
valgrind_all: $(NAME)
	valgrind $(VG_FLAG_ALL) ./$(NAME) 2 900000 60 60 1

dv: d_valgrind
d_valgrind: d
	valgrind $(VG_FLAG) ./$(D_NAME) 2 900000 60 60 1

dva: d_valgrind_all
d_valgrind_all: d
	valgrind $(VG_FLAG_ALL) ./$(D_NAME) 2 900000 60 60 1

h: hel
hel: $(NAME)
	valgrind --tool=helgrind ./$(NAME) 10 400 60 60 2

dh: d_hel
d_hel: d
	valgrind --tool=helgrind ./$(D_NAME) 10 400 60 60 2

.PHONY: v valgrind va valgrind_all dv d_valgrind dva d_valgrind_all h hel dh d_hel

# === [TEST] ===

#	test 200 philosophers
200: $(NAME)
	./$(NAME) 200 120 60 60 1 > $(TXT)
	cat philo.txt

#	test 200 philosophers in debug mode
d_200: d
	./$(D_NAME) 200 500 60 60 1 > $(D_TXT)
	@echo "d_philo.txt"
.PHONY: 200 d_200

# === [TESTER] ===

TESTER_DIR	= ../philosophers_tester/

tester_install:
	git clone https://github.com/kichkiro/philosophers_tester.git $(TESTER_DIR)
	pip3 install -r $(TESTER_DIR)requirements.txt
	make tester

tester:
	python3 $(TESTER_DIR)/src/__main__.py ../philo 

.PHONY: tester_install tester