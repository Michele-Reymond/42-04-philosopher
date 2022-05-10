/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_stop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:48:56 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/10 11:54:01 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_data *data, t_philo *philo)
{
	long int	time;

	while (philo->eat == true)
		usleep(1000);
	time = time_of_meal(data->start_time);
	if (time - philo->last_meal > data->t_die + 1 && data->all_alive == true)
	{
		pthread_mutex_lock(&philo->data->message);
		philo->alive = false;
		data->all_alive = false;
		usleep(100);
		printf(RED "%ld%s%d%s", time, PHILO, philo->id, DEAD); 
		pthread_mutex_unlock(&philo->data->message);
		return (1);
	}
	return (0);
}

int	all_meals_eaten(t_data *data)
{
	long int	time;
	
	time = time_of_meal(data->start_time);
	if (data->philo_ate_all_meals == data->nbr_philo)
	{
		data->philo_ate_all_meals += 1;
		usleep(100);
		pthread_mutex_lock(&(data->message));
		printf(ORANGE "%ld%s%d%s",  time, ALL_ATED, data->must_eat, LEAVE); 
		pthread_mutex_unlock(&(data->message));
		return (1);
	}
	return (0);
}