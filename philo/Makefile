# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/06 15:11:50 by jcourtoi          #+#    #+#              #
#    Updated: 2022/08/10 12:01:25 by jcourtoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo

SRCS =	srcs/philosophers.c srcs/init.c srcs/func.c srcs/checker.c \
	srcs/destroy_mutex.c srcs/exit.c srcs/actions.c srcs/philo_utils.c

INC =	philosophers.h

OBJS =	${SRCS:.c=.o}

CC =	cc

CFLAGS = -Wall -Wextra -Werror -pthread

RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS} ${INC}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all


.PHONY: all clean fclean re
