/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_launch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:54:50 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/10 14:55:37 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_state(t_data *data)
{
	if (data->all_alive && (data->must_eat == 0 
		|| data->philo_ate_all_meals < data->nbr_philo))
			return (0);
	return (1);
}

int	philo_routine(t_data *data, t_philo *philo)
{
	while (!check_state(data))
	{
		if (!check_state(data))
			take_forks(philo);
		if (!check_state(data))
			eat(philo);
		if (!check_state(data))
			sleep_now(philo);
		if (!check_state(data))
			think(philo);
	}
	return (1);
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

int launch_philos(t_data *data, t_philo *philo)
{
	unsigned int	i;

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
	ft_usleep(1000);
	i = 0;
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