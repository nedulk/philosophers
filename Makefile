# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 20:09:16 by kprigent          #+#    #+#              #
#    Updated: 2024/04/26 17:06:14 by kprigent         ###   ########.fr        #
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
		src/free_memory.c \
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

