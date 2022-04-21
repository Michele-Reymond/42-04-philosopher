/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 16:22:26 by mreymond          #+#    #+#             */
/*   Updated: 2021/12/08 16:26:56 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hexwrite(size_t hexa, char lettre, char *str)
{
	int		i;
	char	c;
	int		count;

	i = 0;
	count = 0;
	while (hexa != 0)
	{
		c = hexa % 16;
		if (c >= 0 && c <= 9)
			str[i] = c + 48;
		if (c >= 10 && c <= 15 && (lettre == 'x' || lettre == 'p'))
			str[i] = c + 'a' - 10;
		if (c >= 10 && lettre == 'X')
			str[i] = c + 'A' - 10;
		hexa = hexa / 16;
		i++;
	}
	while (--i > -1)
		write(1, &str[i], 1);
	free(str);
	return (count);
}

int	ft_puthexa(unsigned int hexa, char lettre)
{
	int		count;
	size_t	tmp;
	char	*str;

	count = 0;
	tmp = hexa;
	if (hexa == 0)
	{
		count++;
		write(1, "0", 1);
	}
	while (tmp != 0)
	{
		tmp = tmp / 16;
		count++;
	}
	str = (char *)malloc(sizeof(char) * count);
	if (str == NULL)
		return (0);
	count = count + ft_hexwrite(hexa, lettre, str);
	return (count);
}

int	ft_putadresse(size_t adresse)
{
	int		count;
	size_t	tmp;
	char	*str;

	count = 2;
	tmp = adresse;
	write(1, "0x", 2);
	if (adresse == 0)
	{
		count++;
		write(1, "0", 1);
	}
	while (tmp != 0)
	{
		tmp = tmp / 16;
		count++;
	}
	str = (char *)malloc(sizeof(char) * count);
	if (str == NULL)
		return (0);
	count = count + ft_hexwrite(adresse, 'p', str);
	return (count);
}
