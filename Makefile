# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 16:45:53 by mreymond          #+#    #+#              #
#    Updated: 2022/05/12 16:00:40 by mreymond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS		= 	philo.c \
				philo_errors.c \
				philo_init.c \
				philo_launch.c \
				philo_utils.c \
				philo_actions.c \
				philo_stop.c \
				ft_atoi.c \
				ft_itoa.c \
				ft_isdigit.c \
				ft_strlen.c

OBJS		= $(SRCS:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -g #-fsanitize=address
NAME		= philo
RM			= rm -f

all:		$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

run:	
			./$(NAME) 4 310 200 100

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re run