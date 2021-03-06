/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:37:22 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/12 15:59:32 by mreymond         ###   ########.fr       */
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

# define CYAN		"\033[0;36m"
# define GREEN		"\033[0;32m"
# define DEFAULT	"\033[0m"
# define RED		"\033[0;31m"
# define ORANGE		"\033[0;33m"

# define PHILO		" 	Philo n°"
# define TOOK_FORK	" 	take a fork\n"
# define EAT		" 	is eating his "
# define MEALS		" meal\n"
# define THINK		" 	is thinking\n"
# define SLEEP		" 	is sleeping\n"
# define DEAD		" 	Oops it appear that this philo is dead!\n"
# define ALL_ATED	"	All the Philos ated "
# define LEAVE		" meals and they leave!\n"

typedef struct s_data {
	unsigned int	nbr_philo;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	unsigned int	must_eat;
	unsigned int	philo_ate_all_meals;
	long int		start_time;
	bool			all_alive;
	pthread_mutex_t	message;
}	t_data;

// philosophes
typedef struct s_philo {
	int				id;
	long int		last_meal;
	unsigned int	meals_eaten;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
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
int			philo_routine(t_data *data, t_philo *philo);
int			check_state(t_data *data);
void		*launch(void *arg);
void		eat(t_philo *philo);
void		think(t_philo *philo);
void		sleep_now(t_philo *philo);
void		take_forks(t_philo *philo);
int			philo_init(t_data *data, t_philo *philo);
void		find_left_fork(t_data *data, t_philo *philo);
int			launch_philos(t_data *data, t_philo *philo);
long int	time_of_meal(long int start_time);
void		timer_start(t_data *data);
long int	what_time_is_it(void);
int			all_meals_eaten(t_data *data);
int			is_dead(t_data *data, t_philo *philo);
void		ft_usleep(int sleep);
int			death(t_data *data, t_philo *philo);

#endif
