# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kprigent <kprigent@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 20:09:16 by kprigent          #+#    #+#              #
#    Updated: 2024/01/25 23:25:06 by kprigent         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	src/philo.c \
		src/philo_utils.c 	

OBJS = ${SRCS:.c=.o}

CC = cc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

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
