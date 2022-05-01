/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:37:00 by mreymond          #+#    #+#             */
/*   Updated: 2022/04/26 16:25:18 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo *philo;

	if (check_argc(argc))
		return (EXIT_FAILURE);
	if (args_to_data(argc, argv, &data))
		return (EXIT_FAILURE);
	philo = malloc(sizeof(t_philo) * data.nbr_philo);
	if (philo_init(&data, philo))
		return (EXIT_FAILURE);
	for (unsigned int i = 0; i < data.nbr_philo; i++) {
		pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&philo[i].r_fork);
	}
	// datafree(&data, philo);
	free(philo);
	return (EXIT_SUCCESS);

}

// pthread_create : creer le thread
// pthread_join : attendre la fin de l'execution du thread
// pthread_exit : quitter le thread proprement