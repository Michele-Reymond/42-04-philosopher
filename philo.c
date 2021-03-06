/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:37:00 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/12 13:16:20 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philo;
	unsigned int	i;

	i = 0;
	if (check_argc(argc))
		return (EXIT_FAILURE);
	if (args_to_data(argc, argv, &data))
		return (EXIT_FAILURE);
	philo = malloc(sizeof(t_philo) * data.nbr_philo);
	philo_init(&data, philo);
	while (i < data.nbr_philo)
	{
		pthread_detach(philo[i].thread);
		pthread_mutex_destroy(philo[i].r_fork);
		free(philo[i].r_fork);
		i++;
	}
	pthread_mutex_destroy(&data.message);
	free(philo);
	return (EXIT_SUCCESS);
}
