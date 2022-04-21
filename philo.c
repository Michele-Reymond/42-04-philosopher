/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:37:00 by mreymond          #+#    #+#             */
/*   Updated: 2022/04/21 15:49:27 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_argc(int argc)
{
	if (argc > 7)
	{
		ft_printf("(Error) Too much arguments\n");
		exit(EXIT_FAILURE);
	}
	else if (argc < 5)
	{
		ft_printf("(Error) Too few arguments\n");
		exit(EXIT_FAILURE);
	}
}

void	check_args(char **argv)
{
	(void)argv;
}

int	main(int argc, char **argv)
{
	// struct t_mutex	dictateur;
	// struct t_mutex	fourchettes;

	check_argc(argc);
	check_args(argv);
	return (EXIT_SUCCESS);
}

// pthread_create : creer le thread
// pthread_join : attendre la fin de l'execution du thread
// pthread_exit : quitter le thread proprement