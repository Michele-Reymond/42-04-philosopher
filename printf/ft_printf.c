/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:08:15 by mreymond          #+#    #+#             */
/*   Updated: 2022/01/16 17:01:40 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] != '%')
		{
			write(1, &str[i], 1);
			count++;
		}
		else
		{
			i++;
			count = count + write_argument(str[i], ap);
		}
		i++;
	}
	va_end(ap);
	return (count);
}

/**
 * @brief fonction qui fonctionne comme printf
 * @return int (nbr de charactères imprimés avant le \0)
 * arglist est un objet de type va_list (liste des arguments)
 */
