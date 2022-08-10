# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/05 13:52:12 by jcourtoi          #+#    #+#              #
#    Updated: 2022/08/10 12:01:40 by jcourtoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	philo_bonus

SRCS =	srcs/philosophers_bonus.c srcs/init_bonus.c srcs/func_bonus.c \
	srcs/checker_bonus.c srcs/actions_bonus.c srcs/philo_utils_bonus.c \
	srcs/exit_bonus.c

INC =	philosophers_bonus.h

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
