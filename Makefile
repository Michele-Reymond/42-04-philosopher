# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/20 16:45:53 by mreymond          #+#    #+#              #
#    Updated: 2022/04/21 15:46:38 by mreymond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS		= 	philo.c

OBJS		= $(SRCS:.c=.o)
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra #-g -fsanitize=address
NAME		= philo
RM			= rm -f
PRINTF_PATH	= printf

all:		$(NAME)

$(NAME):	$(OBJS)
			@$(MAKE) --silent -C $(PRINTF_PATH)
			$(CC) $(CFLAGS) $(OBJS) -lpthread -L $(PRINTF_PATH) -lftprintf -o $(NAME)

run:	
			./$(NAME) 5 800 200 200

clean:
			$(RM) $(OBJS)
			@$(MAKE) -C $(PRINTF_PATH) clean

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re run