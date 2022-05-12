/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:37:00 by mreymond          #+#    #+#             */
/*   Updated: 2022/05/12 14:41:09 by mreymond         ###   ########.fr       */
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

long int	what_time_is_it()
{
	struct timeval	time;
	long int		time_now;

	gettimeofday(&time, NULL);
	time_now = ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (time_now);
}

void timer_start(t_data *data)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	data->start_time = (time.tv_sec * 1000) + (time.tv_usec / 1000);
}
