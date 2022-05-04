/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:37:22 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/02 18:16:11 by mreymond         ###   ########.fr       */
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
# include <stdbool.h>
# include "printf/ft_printf.h"

// données de bases:
// number_of_philosophers
// time_to_die
// time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]
typedef struct s_data {
	unsigned int	nbr_philo;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	must_eat;
	unsigned int	philo_ate_all_meals;
	long int		start_time;
	int				*philo_order;
	bool			all_alive;
	pthread_mutex_t	message;
}	t_data;

// philosophes
typedef struct s_philo {
	int				id;
	long int		last_meal;
	unsigned int	meals_eaten;
	pthread_mutex_t	r_fork;
	pthread_mutex_t	l_fork;
	pthread_t		thread;
	t_data			*data;
	bool			alive;
}	t_philo;

int			ft_isdigit(int d);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
size_t		ft_strlen(const char *str);
int			args_to_data(int argc, char **argv, t_data *data);
int			check_argc(int argc);
int			args_is_digit(int argc, char **argv);
int			args_max_min(int argc, char **argv);
int			check_args(int argc, char **argv);
int			check_errors(int argc, char **argv);
void		*test(void *arg);
int			philo_init(t_data *data, t_philo *philo);
void		datafree(t_data *data, t_philo *philo);
char		*time_str(long int start_time);
long int	time_of_meal(long int start_time);
int			philo_routine(t_data *data, t_philo *philo);
void		eat(t_philo *philo);
void		think(t_philo *philo);
void		sleep_now(t_philo *philo);
void		take_forks(t_philo *philo);

#endif

// MALLOC
// dans la fonction args_to_data