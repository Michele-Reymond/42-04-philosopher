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

void	write_range(int *range)
{
	int i;
	char *a;

	i = 0;
	write(1, "\n", 1);
	while (range[i])
	{
		a = ft_itoa(range[i]);
		write(1, a, 1);
		write(1, ", ", 2);
		i++;
	}
	write(1, "\n", 1);
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
	long int	time;
	char *eat_time;

	time = time_of_meal(data->start_time);

	id = ft_itoa(philo->id);
	if (time - philo->last_meal > data->t_die)
	{
		philo->alive = false;
		data->all_alive = false;
		eat_time = time_str(philo->data->start_time);
		pthread_mutex_lock(&philo->data->message);
		write(1, eat_time, ft_strlen(eat_time));
		write(1, " philo dead here!!!  ", 21);
		write(1, id, ft_strlen(id));
		write(1, "\n", 1);
		pthread_mutex_unlock(&philo->data->message);
		return (1);
	}
	return (0);
}

int	all_meals_eaten(t_data *data)
{
	if (data->philo_ate_all_meals == data->nbr_philo)
	{
		data->philo_ate_all_meals += 1;
		pthread_mutex_lock(&(data->message));
		write(1, "All meals eaten!!!\n", 19);
		pthread_mutex_unlock(&(data->message));
		return (1);
	}
	return (0);
}

int	philo_routine(t_data *data, t_philo *philo)
{
	while (1)
	{
		if (data->philo_order[data->nbr_philo - 1] != philo->id && data->all_alive == true) 
		{
			take_forks(philo);
			eat(philo);
		}
		if (data->all_alive == false || all_meals_eaten(data) || is_dead(data, philo) || data->philo_ate_all_meals > data->nbr_philo)
		{
			return (1);
		}
		if (data->all_alive == true) 
			sleep_now(philo);
		if (data->all_alive == false || all_meals_eaten(data) || is_dead(data, philo) || data->philo_ate_all_meals > data->nbr_philo)
		{
			return (1);
		}
		if (data->all_alive == true) 
			think(philo);
		if (data->all_alive == false || all_meals_eaten(data) || is_dead(data, philo) || data->philo_ate_all_meals > data->nbr_philo)
		{
			return (1);
		}
		usleep(10);
	}
	return (0);
}

void	update_order(int *order, int id, unsigned int nbr_p)
{
	unsigned int i;
	int	tmp;

	i = 0;
	tmp = order[nbr_p - 1];
	while (i < nbr_p)
	{
		if (order[i] == id)
			break ;
		i++;
	}
	order[nbr_p - 1] = order[i];
	while (i < nbr_p - 2)
	{
		order[i] = order[i + 1];
		i++;
	}
	order[i] = tmp;
}

void	take_forks(t_philo *philo)
{
	char	*id;
	char	*time;

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
	pthread_mutex_unlock(&philo->data->message);
	free(id);
	free(time);
}


void	eat(t_philo *philo)
{
	char	*id;
	char	*eaten;
	char	*eat_time;

	id = ft_itoa(philo->id);
	eat_time = time_str(philo->data->start_time);
	pthread_mutex_lock(&philo->data->message);
	write(1, eat_time, ft_strlen(eat_time));
	write(1, "	Philosopher n° ", 16);
	write(1, id, ft_strlen(id));
	write(1, "	 is eating", 12);
	write(1, "	 for the ", 10);
	update_order(philo->data->philo_order, philo->id, philo->data->nbr_philo);
	philo->meals_eaten += 1;
	eaten = ft_itoa(philo->meals_eaten);
	write(1, eaten, ft_strlen(eaten));
	write(1, " meal\n", 6);
	if (philo->meals_eaten == philo->data->must_eat)
		philo->data->philo_ate_all_meals += 1;
	pthread_mutex_unlock(&philo->data->message);
	usleep(philo->data->t_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
	free(id);
	free(eaten);
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
	pthread_mutex_unlock(&philo->data->message);
	usleep(philo->data->t_sleep);
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
	philo_routine(data, philo);
	return (NULL);
}

int	args_to_data(int argc, char **argv, t_data *data)
{
	if (check_args(argc, argv))
		return (1);
	data->nbr_philo = ft_atoi(argv[1]);
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]) * 1000;
	data->t_sleep = ft_atoi(argv[4]) * 1000;
	data->philo_ate_all_meals = 0;
	data->all_alive = true;
	data->philo_order = malloc(sizeof(int) * data->nbr_philo);
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
		philo[i].data->philo_order[i] = philo[i].id;
		philo[i].meals_eaten = 0;
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
		if (philo[i].id % 2 == 0)
		{
			if (pthread_create(&philo[i].thread, NULL, try_to_eat, &philo[i]) != 0)
				return (1);		
		}
		i++;
	}
	i = 0;
	usleep(10);
	while (i < data->nbr_philo)
	{
		if (philo[i].id % 2 != 0)
		{
			if (pthread_create(&philo[i].thread, NULL, try_to_eat, &philo[i]) != 0)
				return (1);		
		}
		i++;
	}
	return (0);
}
