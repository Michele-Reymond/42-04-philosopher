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
	// struct s_philo	*philo;
	struct s_data	data;

	if (check_argc(argc))
		return (EXIT_FAILURE);
	else if (args_to_data(argc, argv, &data))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// pthread_create : creer le thread
// pthread_join : attendre la fin de l'execution du thread
// pthread_exit : quitter le thread proprement