/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 16:23:46 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/12 16:00:02 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_argc(int argc)
{
	if (argc > 7)
	{
		printf("(Error) Too much arguments\n");
		return (1);
	}
	else if (argc < 5)
	{
		printf("(Error) Too few arguments\n");
		return (1);
	}
	return (0);
}

int	args_is_digit(int argc, char **argv)
{
	int	i;
	int	j;

	j = 1;
	while (j < argc)
	{
		i = 0;
		while (argv[j][i])
		{
			if (!ft_isdigit(argv[j][i]))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	args_max_min(int argc, char **argv)
{
	int	j;

	j = 1;
	while (j < argc)
	{
		if (ft_strlen(argv[j]) == 10 && argv[j][9] < '7')
			return (1);
		else if (ft_strlen(argv[j]) > 10)
			return (1);
		j++;
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	if (args_is_digit(argc, argv))
	{
		printf("(Error) There is a non-digit in arguments\n");
		return (1);
	}
	if (args_max_min(argc, argv))
	{
		printf("(Error) One or more argument(s) are greater than MAX\n");
		return (1);
	}
	return (0);
}

int	check_errors(int argc, char **argv)
{
	if (args_is_digit(argc, argv))
	{
		printf("(Error) There is a non-digit in arguments\n");
		return (1);
	}
	if (args_max_min(argc, argv))
	{
		printf("(Error) Arguments are greater than MAX\n");
		return (1);
	}
	return (0);
}
