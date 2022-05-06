/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:24:52 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/06 11:47:34 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_routine(t_data *data, t_philo *philo)
{
	while (1)
	{
		if ((data->philo_order[data->nbr_philo - 1] != philo->id || data->nbr_philo < 3) && data->all_alive == true && (philo->meals_eaten < data->must_eat || data->must_eat == 0)) 
		{
			take_forks(philo);
			eat(philo);
		}
		if (is_dead(data, philo) || all_meals_eaten(data))
		{
			return (1);
		}
		if (data->all_alive == true && (philo->meals_eaten < data->must_eat || data->must_eat == 0)) 
			sleep_now(philo);
		if (is_dead(data, philo) || all_meals_eaten(data))
		{
			return (1);
		}
		if (data->all_alive == true && (philo->meals_eaten < data->must_eat || data->must_eat == 0)) 
			think(philo);
		if (is_dead(data, philo) || all_meals_eaten(data))
		{
			return (1);
		}
		usleep(10);
	}
	return (0);
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
	if (data->t_die < 60 || data->t_eat < 60 || data->t_sleep < 60)
		return (0);
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

int	death(t_data *data, t_philo *philo)
{
	unsigned int i;

	while (1)
	{
		i = 0;
		while (i < data->nbr_philo)
		{
			if (is_dead(data, &philo[i]) || all_meals_eaten(data))
				return (1);
			i++;			
		}
	}
	return (0);
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
		philo[i].r_fork = malloc(sizeof(pthread_mutex_t));
		if (pthread_mutex_init(philo[i].r_fork, NULL) != 0)
			return (1);
		i++;
	}
	i = 0; 
	while (i < data->nbr_philo)
	{
		if (i == 0)
		{
			if (data->nbr_philo == 1)
				philo[i].l_fork = philo[i].r_fork;
			else
				philo[i].l_fork = philo[data->nbr_philo - 1].r_fork;
		}
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
			usleep(1000);	
		}
		i++;
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		if (philo[i].id % 2 != 0)
		{
			if (pthread_create(&philo[i].thread, NULL, try_to_eat, &philo[i]) != 0)
				return (1);	
			usleep(1000);	
		}
		i++;
	}
	if (death(data, philo))
		return (1);
	return (0);
}
