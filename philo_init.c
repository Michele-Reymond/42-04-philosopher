/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:24:52 by mreymond          #+#    #+#             */
/*   Updated: 2022/04/26 16:25:12 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*actual_time(long int start_time)
{
	struct timeval	time;
	long int	time_now;
	char		*time_diff;

	gettimeofday(&time, NULL);
	// time_now = ((time.tv_usec + time.tv_sec * 1000000) - start_time) / 1000;
	time_now = ((time.tv_usec + time.tv_sec * 1000000) - start_time);
	time_diff = ft_itoa(time_now);
	return (time_diff);
}

void		eat(t_philo *philo)
{
	char *id;
	char *time;
	char *eat_time;

	id = ft_itoa(philo->id);
	pthread_mutex_lock(&philo->r_fork);
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->message);
	time = actual_time(philo->data->start_time);
	write(1, time, ft_strlen(time));
	write(1, " Philosopher n° ", 16);
	write(1, id, ft_strlen(id));
	write(1, " took is right and left fork\n", 29);
	eat_time = actual_time(philo->data->start_time);
	write(1, eat_time, ft_strlen(eat_time));
	write(1, " Philosopher n° ", 16);
	write(1, id, ft_strlen(id));
	write(1, " is eating\n", 11);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(&philo->message);
	usleep(10);
	free(id);
	free(time);
	free(eat_time);
}

void		sleep_now(t_philo *philo)
{
	char *id;
	char *time;

	id = ft_itoa(philo->id);
	pthread_mutex_lock(&philo->message);
	time = actual_time(philo->data->start_time);
	write(1, time, ft_strlen(time));
	write(1, " Philosopher n° ", 16);
	write(1, id, ft_strlen(id));
	write(1, " is sleeping\n", 13);
	pthread_mutex_unlock(&philo->message);
	usleep(10);
	free(id);
	free(time);
}

void		think(t_philo *philo)
{
	char *id;
	char *time;

	id = ft_itoa(philo->id);
	pthread_mutex_lock(&philo->message);
	time = actual_time(philo->data->start_time);
	write(1, time, ft_strlen(time));
	write(1, " Philosopher n° ", 16);
	write(1, id, ft_strlen(id));
	write(1, " is thinking\n", 13);
	pthread_mutex_unlock(&philo->message);
	usleep(10);
	free(id);
	free(time);
}

void *try_to_eat(void *arg)
{
	t_data		*data;
	t_philo		*philo;

	philo = (t_philo *)arg;
	data = philo->data;
	(void)data;
	eat(philo);
	sleep_now(philo);
	think(philo);

	pthread_exit(EXIT_SUCCESS);
}

int	args_to_data(int argc, char **argv, t_data *data)
{
	if (check_args(argc, argv))
		return (1);
	data->nbr_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = 0;
	return (0);
}

void timer_start(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	data->start_time = time.tv_usec + time.tv_sec * 1000000;
}

int	philo_init(t_data *data, t_philo *philo)
{
	unsigned int i;

	i = 0;
	timer_start(data);
	while (i < data->nbr_philo)
	{
		philo[i].id = i;
		philo[i].last_meal = 0;
		philo[i].data = data;
		if (pthread_mutex_init(&philo[i].message, NULL) != 0)
			return (1);
		if (pthread_mutex_init(&philo[i].r_fork, NULL) != 0)
			return (1);
		if (i == 0)
			philo[i].l_fork = philo[data->nbr_philo  - 1].r_fork;
		else
			philo[i].l_fork = philo[i - 1].r_fork;
		if (pthread_create(&philo[i].thread, NULL, try_to_eat, &philo[i]) != 0)
			return (1);
		usleep(10);
		i++;
	}
	return (0);
}

void	datafree(t_data *data, t_philo *philo)
{
	free(philo);
	free(data);
}

