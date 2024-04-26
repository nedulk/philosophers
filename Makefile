# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 20:09:16 by kprigent          #+#    #+#              #
#    Updated: 2024/04/26 14:27:22 by kprigent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	src/philo.c \
		src/init.c \
		src/philo_utils.c \
		src/forks_handle.c \
		src/actions_philo.c \
		src/check_death.c \
		src/parsing.c \
		src/start_thread.c

OBJS = ${SRCS:.c=.o}

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g 

.c.o:
	${CC} ${CFLAGS} -I includes -c $< -o ${<:.c=.o}


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I includes $(OBJS) -o $(NAME)
	
all: $(NAME)

clean:
	${RM} ${OBJS} clean

fclean: clean
	${RM} ${NAME} fclean

re:	fclean all

.PHONY: all clean fclean re

# - ./philo 1 200 200 200    philo 1 ne prend qu'une fourchette et meurt au bout de 200 ms
# - ./philo 2 800 200 200    personne ne meurt
# - ./philo 5 800 200 200    personne ne meurt
# - ./philo 5 800 200 200 7    la simulation s'arrete quand chaque philo a mange 7 fois // actions apres "everyone ate"
# - ./philo 4 410 200 200    personne ne meurt
# - ./philo 4 310 200 200    un philo meurt
# - ./philo 4 500 200 1.2    argument invalide
# - ./philo 4 0 200 200    argument invalide // pas gere
# - ./philo 4 -500 200 200    argument invalide
# - ./philo 4 500 200 2147483647    un philo meurt au bout de 500 ms
# - ./philo 4 2147483647 200 200    personne ne meurt
# - ./philo 4 214748364732 200 200    argument invalide
# - ./philo 4 200 210 200    un philo meurt, il faut afficher la mort avant 210 ms
# - valgrind --tool=helgrind ou valgrind --tool=drd
# ./philo 2 250 150 100 pb
