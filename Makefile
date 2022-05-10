# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 16:45:53 by mreymond          #+#    #+#              #
#    Updated: 2022/05/10 14:56:22 by mreymond         ###   ########.fr        #
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
PRINTF_PATH	= printf

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(MAKE) --silent -C $(PRINTF_PATH)
			$(CC) $(CFLAGS) $(OBJS) -lpthread -L $(PRINTF_PATH) -lftprintf -o $(NAME)

run:	
			./$(NAME) 4 310 200 100

clean:
			$(RM) $(OBJS)
			@$(MAKE) -C $(PRINTF_PATH) clean

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re run