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

void *test(void *arg)
{
	(void)arg;
	ft_printf("Coucou\n");
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

int	philo_init(t_data *data, t_philo **philo)
{
	unsigned int i;

	i = 0;
	data->threads = malloc(sizeof(pthread_t) * data->nbr_philo);
	while (i < data->nbr_philo)
	{
		philo[i] = malloc(sizeof(t_philo));
		philo[i]->id = i;
		philo[i]->last_meal = 0;
		if (pthread_mutex_init(&philo[i]->r_fork, NULL) != 0) {
			ft_printf("(Error) Mutex init failed\n");
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < data->nbr_philo)
	{
		if (pthread_create(&data->threads[i], NULL, test, &philo[i])!= 0) {
			ft_printf("Echec de la création du thread: [%u]", i);
			return (1);
		}
		ft_printf("Création du thread numéro %u\n", i);
		i++;
	}
	return (0);
}
