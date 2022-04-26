/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:37:22 by mreymond          #+#    #+#             */
/*   Updated: 2022/04/26 16:30:05 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include "printf/ft_printf.h"

// philosophes
typedef struct s_philo {
	int				id;
	int				last_meal;
	pthread_mutex_t	fork1;
	pthread_mutex_t	fork2;
}	t_philo;

// données de bases
typedef struct s_data {
	unsigned int	nbr_philo;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	must_eat;
}	t_data;

int		ft_isdigit(int d);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
int		args_to_data(int argc, char **argv, t_data *data);
int		check_argc(int argc);
int		args_is_digit(int argc, char **argv);
int		args_max_min(int argc, char **argv);
int		check_args(int argc, char **argv);
int		check_errors(int argc, char **argv);

#endif