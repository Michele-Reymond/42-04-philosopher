# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 16:45:53 by mreymond          #+#    #+#              #
#    Updated: 2022/04/26 16:27:20 by mreymond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS		= 	philo.c \
				philo_errors.c \
				philo_init.c \
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
			./$(NAME) 3 800 200 200

clean:
			$(RM) $(OBJS)
			@$(MAKE) -C $(PRINTF_PATH) clean

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re run

# FONCTIONE AUTORISEES
# memset, printf, malloc, free, write,
# usleep, gettimeofday, pthread_create,
# pthread_detach, pthread_join, pthread_mutex_init,
# pthread_mutex_destroy, pthread_mutex_lock,
# pthread_mutex_unlock