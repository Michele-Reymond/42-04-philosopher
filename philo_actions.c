/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:47:09 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/04 23:13:52 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	char	*time;

	pthread_mutex_lock(&philo->r_fork);
	pthread_mutex_lock(&philo->l_fork);
	pthread_mutex_lock(&philo->data->message);
	time = time_str(philo->data->start_time);
	philo->last_meal = time_of_meal(philo->data->start_time);
    printf(CYAN "%s%s%d%s", time, PHILO, philo->id, TOOK_FORK); 
	pthread_mutex_unlock(&philo->data->message);
	free(time);
}

void	eat(t_philo *philo)
{
	char	*eat_time;

	eat_time = time_str(philo->data->start_time);
	pthread_mutex_lock(&philo->data->message);
	update_order(philo->data->philo_order, philo->id, philo->data->nbr_philo);
	philo->meals_eaten += 1;
    printf(GREEN "%s%s%d%s%d%s", eat_time, PHILO, 
        philo->id, EAT, philo->meals_eaten, MEALS); 
	if (philo->meals_eaten == philo->data->must_eat)
		philo->data->philo_ate_all_meals += 1;
	pthread_mutex_unlock(&philo->data->message);
	usleep(philo->data->t_eat);
	pthread_mutex_unlock(&philo->l_fork);
	pthread_mutex_unlock(&philo->r_fork);
	free(eat_time);
}

void	think(t_philo *philo)
{
	char	*time;

	pthread_mutex_lock(&philo->data->message);
	time = time_str(philo->data->start_time);
    printf(DEFAULT "%s%s%d%s", time, PHILO, philo->id, THINK); 
	pthread_mutex_unlock(&philo->data->message);
	free(time);
}

void	sleep_now(t_philo *philo)
{
	char	*time;

	pthread_mutex_lock(&philo->data->message);
	time = time_str(philo->data->start_time);
    printf(DEFAULT "%s%s%d%s", time, PHILO, philo->id, SLEEP); 
	pthread_mutex_unlock(&philo->data->message);
	usleep(philo->data->t_sleep);
	free(time);
}