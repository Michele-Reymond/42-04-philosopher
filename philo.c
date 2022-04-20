/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:37:00 by mreymond          #+#    #+#             */
/*   Updated: 2022/04/20 17:00:37 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_1(void *arg)
{
	(void)arg;
	printf("Nous sommes dans le thread.\n");
	pthread_exit(EXIT_SUCCESS);
}

int	main(void)
{
	pthread_t	thread1;

	printf("Avant la création du thread.\n");
	pthread_create(&thread1, NULL, thread_1, NULL);
	printf("Après la création du thread.\n");
	return (EXIT_SUCCESS);
}
