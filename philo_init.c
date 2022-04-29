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

void *try_to_eat(void *arg)
{
	t_philo *philo = (t_philo *) arg;

	pthread_mutex_lock(&(*philo).r_fork);
	write(1, "Philosopher took is right fork\n", 31);
	pthread_mutex_lock(&(*philo).l_fork);
	write(1, "Philosopher took is left fork\n", 31);
	write(1, "Philosopher is eating\n", 22);

	// Dévérouillage du mutex
	pthread_mutex_unlock(&(*philo).r_fork);
	pthread_mutex_unlock(&(*philo).l_fork);

	// Pause l'exécution du thread pendant 1 seconde
	usleep(10);

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

void	actual_time(long int start_time)
{
	struct timeval	time;
	long int	time_now;

	gettimeofday(&time, NULL);
	time_now = ((time.tv_usec + time.tv_sec * 1000000) - start_time) / 1000;
	printf("ici: %ld\n", time_now);
}

int	philo_init(t_data *data, t_philo *philo)
{
	unsigned int i;

	i = 0;
	data->threads = malloc(sizeof(pthread_t) * data->nbr_philo);
	timer_start(data);
	while (i < data->nbr_philo)
	{
		// philo[i] = malloc(sizeof(t_philo));
		philo[i].id = i;
		philo[i].last_meal = 0;
		philo[i].data = data;
		if (pthread_mutex_init(&philo[i].r_fork, NULL) != 0)
			return (1);
		if (pthread_create(&data->threads[i], NULL, try_to_eat, &philo[i]) != 0)
			return (1);
		i++;
	}
	actual_time(data->start_time);
	return (0);
}

void	datafree(t_data *data, t_philo *philo)
{
	// unsigned int i;

	// i = 0;
	// while (i < data->nbr_philo)
	// {
	// 	free(philo[i]);
	// 	i++;
	// }
	free(philo);
	free(data);
}

