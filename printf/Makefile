# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/17 16:14:57 by mreymond          #+#    #+#              #
#    Updated: 2022/04/18 17:33:06 by mreymond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_printf.c \
	ft_printf_utils.c \
	ft_printf_unsigned.c \
	ft_printf_hexa.c
CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=address
CC = gcc
NAME = libftprintf.a
OBJS = ${SRCS:.c=.o}
AR = ar rc
RM = rm -f

all: ${NAME}

$(NAME): ${OBJS}
		${AR} ${NAME} ${OBJS}

clean: 
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

bonus: