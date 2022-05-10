/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 21:47:09 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/10 14:45:26 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int sleep)
{
	long int	sleeping_end;

	sleeping_end = what_time_is_it() + sleep / 1000;
	while (what_time_is_it() < sleeping_end)
		usleep(100);
}

void	take_forks(t_philo *philo)
{
	long int	t;

	t = philo->data->start_time;
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->data->message);
	printf(CYAN "%ld%s%d%s", time_of_meal(t), PHILO, philo->id, TOOK_FORK);
	pthread_mutex_unlock(&philo->data->message);
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->data->message);
	printf(CYAN "%ld%s%d%s", time_of_meal(t), PHILO, philo->id, TOOK_FORK); 
	pthread_mutex_unlock(&philo->data->message);
}

void	eat(t_philo *philo)
{
	long int	t;

	t = philo->data->start_time;
	pthread_mutex_lock(&philo->data->message);
    printf(GREEN "%ld%s%d%s%d%s", time_of_meal(t), PHILO, 
        philo->id, EAT, philo->meals_eaten + 1, MEALS); 
	pthread_mutex_unlock(&philo->data->message);
	philo->meals_eaten += 1;
	if (philo->meals_eaten == philo->data->must_eat)
		philo->data->philo_ate_all_meals += 1;
	philo->last_meal = time_of_meal(t);
	ft_usleep(philo->data->t_eat);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	think(t_philo *philo)
{
	long int	t;

	t = philo->data->start_time;
	pthread_mutex_lock(&philo->data->message);
    printf(DEFAULT "%ld%s%d%s", time_of_meal(t), PHILO, philo->id, THINK);
	pthread_mutex_unlock(&philo->data->message);
}

void	sleep_now(t_philo *philo)
{
	long int	t;

	t = philo->data->start_time;
	pthread_mutex_lock(&philo->data->message);
    printf(DEFAULT "%ld%s%d%s", time_of_meal(t), PHILO, philo->id, SLEEP); 
	pthread_mutex_unlock(&philo->data->message);
	ft_usleep(philo->data->t_sleep);
}