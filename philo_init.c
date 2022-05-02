/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:24:52 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/02 18:34:34 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	time_of_meal(long int start_time)
{
	struct timeval	time;
	long int		time_now;

	gettimeofday(&time, NULL);
	time_now = ((time.tv_usec + time.tv_sec * 1000000) - start_time) / 1000;
	return (time_now);
}

char	*time_str(long int start_time)
{
	char			*time_diff;

	time_diff = ft_itoa(time_of_meal(start_time));
	return (time_diff);
}

int	is_dead(t_data *data, t_philo *philo)
{
	char	*id;
	int long time;
	int long	time2;

	id = ft_itoa(philo->id);
	time = philo->last_meal + data->t_die;
	time2 = time_of_meal(data->start_time);
	if (time_of_meal(data->start_time) - philo->last_meal > data->t_die)
	{
		philo->alive = false;
		write(1, id, ft_strlen(id));
		write(1, " philo dead here!!!\n", 19);
		return (1);
	}
	return (0);
}

int	all_meals_eaten(t_data *data)
{
	if (data->meals_eaten > data->must_eat)
	{
		write(1, "All meals eaten!!!\n", 19);
		return (1);
	}
	return (0);
}

int	philo_routine(t_data *data, t_philo *philo)
{
	while (1)
	{
		eat(philo);
		if (all_meals_eaten(data) || is_dead(data, philo))
			return (1);
		sleep_now(philo);
		if (all_meals_eaten(data) || is_dead(data, philo))
			return (1);
		think(philo);
		if (all_meals_eaten(data) || is_dead(data, philo))
			return (1);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	char	*id;
	char	*time;
	char	*eat_time;

	id = ft_itoa(philo->id);
	pthread_mutex_lock(&philo->r_fork);
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->data->message);
	time = time_str(philo->data->start_time);
	philo->last_meal = time_of_meal(philo->data->start_time);
	write(1, time, ft_strlen(time));
	write(1, "	Philosopher n° ", 16);
	write(1, id, ft_strlen(id));
	write(1, "	 took is right and left fork\n", 30);
	eat_time = time_str(philo->data->start_time);
	write(1, eat_time, ft_strlen(eat_time));
	write(1, "	Philosopher n° ", 16);
	write(1, id, ft_strlen(id));
	write(1, "	 is eating\n", 12);
	philo->data->meals_eaten += 1;
	usleep(philo->data->t_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(&philo->data->message);
	free(id);
	free(time);
	free(eat_time);
	usleep(10);
}

void	sleep_now(t_philo *philo)
{
	char	*id;
	char	*time;

	id = ft_itoa(philo->id);
	pthread_mutex_lock(&philo->data->message);
	time = time_str(philo->data->start_time);
	write(1, time, ft_strlen(time));
	write(1, "	Philosopher n° ", 16);
	write(1, id, ft_strlen(id));
	write(1, "	 is sleeping\n", 14);
	usleep(philo->data->t_sleep);
	pthread_mutex_unlock(&philo->data->message);
	free(id);
	free(time);
}

void	think(t_philo *philo)
{
	char	*id;
	char	*time;

	id = ft_itoa(philo->id);
	pthread_mutex_lock(&philo->data->message);
	time = time_str(philo->data->start_time);
	write(1, time, ft_strlen(time));
	write(1, "	Philosopher n° ", 16);
	write(1, id, ft_strlen(id));
	write(1, "	 is thinking\n", 14);
	pthread_mutex_unlock(&philo->data->message);
	free(id);
	free(time);
}

void	*try_to_eat(void *arg)
{
	t_data		*data;
	t_philo		*philo;

	philo = (t_philo *)arg;
	data = philo->data;
	if (philo_routine(data, philo))
		pthread_exit(EXIT_SUCCESS);
	pthread_exit(EXIT_SUCCESS);
}

int	args_to_data(int argc, char **argv, t_data *data)
{
	if (check_args(argc, argv))
		return (1);
	data->nbr_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]) * 1000;
	data->t_eat = ft_atoi(argv[3]) * 1000;
	data->t_sleep = ft_atoi(argv[4]) * 1000;
	data->meals_eaten = 0;
	if (pthread_mutex_init(&data->message, NULL) != 0)
		return (1);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5]);
	else if (argc == 6 && (ft_atoi(argv[5]) == 0))
		return (1);
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
	unsigned int	i;

	i = 0;
	timer_start(data);
	while (i < data->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].last_meal = 0;
		philo[i].alive = true;
		philo[i].data = data;
		if (pthread_mutex_init(&philo[i].r_fork, NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		if (i == 0)
			philo[i].l_fork = philo[data->nbr_philo - 1].r_fork;
		else
			philo[i].l_fork = philo[i - 1].r_fork;
		i++;
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		if (philo->id % 2 == 0)
		{
			if (pthread_create(&philo[i].thread, NULL, try_to_eat, &philo[i]) != 0)
				return (1);		
		}
		i++;
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		if (philo->id % 2 != 0)
		{
			if (pthread_create(&philo[i].thread, NULL, try_to_eat, &philo[i]) != 0)
				return (1);		
		}
		i++;
	}
	return (0);
}
