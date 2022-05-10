/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:37:00 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/10 11:34:01 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	time_of_meal(long int start_time)
{
	struct timeval	time;
	long int		time_now;

	gettimeofday(&time, NULL);
	time_now = ((time.tv_sec * 1000) + (time.tv_usec / 1000)) - start_time;
	return (time_now);
}

void timer_start(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	data->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

char	*time_str(long int start_time)
{
	char			*time_diff;

	time_diff = ft_itoa(time_of_meal(start_time));
	return (time_diff);
}

void	update_order(int *order, int id, unsigned int nbr_p)
{
	unsigned int i;
	int	tmp;

	i = 0;
	if (nbr_p == 1)
		return ;
	tmp = order[nbr_p - 1];
	while (i < nbr_p)
	{
		if (order[i] == id)
			break ;
		i++;
	}
	order[nbr_p - 1] = order[i];
	while (i < nbr_p - 2)
	{
		order[i] = order[i + 1];
		i++;
	}
	order[i] = tmp;
}
