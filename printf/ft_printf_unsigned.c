/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:23:23 by mreymond          #+#    #+#             */
/*   Updated: 2021/11/26 16:23:55 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsigned(int s)
{
	unsigned int	u;
	char			ptr[10];
	int				i;
	int				count;

	i = 0;
	count = 0;
	u = s + UINT_MAX + 1;
	if (u == 0)
	{
		write(1, "0", 1);
		count++;
	}
	while (u > 0)
	{
		ptr[i] = u % 10 + 48;
		u /= 10;
		count++;
		i++;
	}
	while (--i > -1)
		write(1, &ptr[i], 1);
	return (count);
}
