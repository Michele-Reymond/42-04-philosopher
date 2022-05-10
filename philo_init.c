/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:24:52 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/10 11:43:34 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_state(t_data *data)
{
	if (data->all_alive || data->philo_ate_all_meals < data->nbr_philo)
		return (0);
	return (1);
}

int	philo_routine(t_data *data, t_philo *philo)
{

	while (1)
	{
		if (!check_state(data))
			take_forks(philo);
		if (!check_state(data))
			eat(philo);
		if (!check_state(data))
			sleep_now(philo);
		if (!check_state(data))
			think(philo);
		if (check_state(data))
			return (1);
	}

	// while (1)
	// {
	// 	if (data->all_alive == true && (philo->meals_eaten < data->must_eat || data->must_eat == 0)) 
	// 	{
	// 		if (data->philo_order[0] == philo->id || data->philo_order[1] == philo->id || philo->last_meal == 0)
	// 		{
	// 			take_forks(philo);
	// 			if (data->all_alive == true && !(is_dead(data, philo))) 
	// 				eat(philo);
	// 		}
	// 	}
	// 	if (is_dead(data, philo) || all_meals_eaten(data))
	// 		return (1);
	// 	else if (data->all_alive == true && (philo->meals_eaten < data->must_eat || data->must_eat == 0)) 
	// 	{
	// 		sleep_now(philo);
	// 		if (data->all_alive == true && (philo->meals_eaten < data->must_eat || data->must_eat == 0)) 
	// 			think(philo);
	// 	}
	// }
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
	// data->philo_order = malloc(sizeof(int) * data->nbr_philo);
	if (pthread_mutex_init(&data->message, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&data->death, NULL) != 0)
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
	while (i < data->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].last_meal = 0;
		philo[i].alive = true;
		philo[i].eat = false;
		philo[i].data = data;
		// philo[i].data->philo_order[i] = philo[i].id;
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
	timer_start(data);
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
	usleep(10);
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
	if (death(data, philo))
		return (1);
	return (0);
}
