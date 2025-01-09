# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dancel <dancel@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/03 08:30:41 by grlefebv          #+#    #+#              #
#    Updated: 2024/10/24 18:23:16 by dancel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRCS =	ft_printf.c\
		ft_put*.c

LIBC = ar rcs
CC = cc
FLAG = -Wall -Wextra -Werror
OBJS = ${SRCS:.c=.o}
OBJSB = ${SRCB:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

.c.o:
	$(CC) $(FLAG) -c $(<) -o $(<:.c=.o)

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
