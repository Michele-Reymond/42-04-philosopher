/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@42lausanne.ch>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:03:52 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/03 23:12:58 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	itoa_count(long int n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		neg;
	int		len;
	char	*str;

	neg = 1;
	if (n < 0)
		neg = -1;
	len = itoa_count(n);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	while (--len > -1)
	{
		str[len] = (n % 10) * neg + 48;
		n /= 10;
	}
	if (neg < 0)
		str[0] = '-';
	return (str);
}

// Alloue (avec malloc(3)) et retourne une chaine de
// caractères représentant l’integer reçu en argument.
// Les nombres négatifs doivent être gérés.

// PARAMS
// #1. l’integer à convertir.

// RETURN
// La chaine de caractères représentant l’integer.
// NULL si l’allocation échoue.