/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 17:14:01 by mreymond          #+#    #+#             */
/*   Updated: 2021/11/26 16:24:20 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbrwrite(int n)
{
	int		i;
	char	ptr[12];
	int		count;

	i = 0;
	count = 0;
	while (n > 0)
	{
		ptr[i] = n % 10 + 48;
		n /= 10;
		count++;
		i++;
	}
	while (--i > -1)
		write(1, &ptr[i], 1);
	return (count);
}

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n == INT_MIN)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n == 0)
	{
		count++;
		write(1, "0", 1);
	}
	if (n < 0)
	{
		count++;
		n = -n;
		write(1, "-", 1);
	}
	count = count + ft_putnbrwrite(n);
	return (count);
}

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *s)
{
	int	i;

	i = -1;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[++i] != '\0')
		write(1, &s[i], 1);
	return (i);
}

int	write_argument(char argument, va_list ap)
{
	int	count;

	count = 0;
	if (argument == 'd' || argument == 'i')
		count = ft_putnbr(va_arg(ap, int));
	else if (argument == 'u')
		count = ft_putunsigned(va_arg(ap, int));
	else if (argument == 'c')
		count = ft_putchar(va_arg(ap, int));
	else if (argument == 's')
		count = ft_putstr(va_arg(ap, char *));
	else if (argument == 'p')
		count = ft_putadresse(va_arg(ap, size_t));
	else if (argument == 'x')
		count = ft_puthexa(va_arg(ap, unsigned int), 'x');
	else if (argument == 'X')
		count = ft_puthexa(va_arg(ap, unsigned int), 'X');
	else if (argument == '%')
	{
		count = 1;
		write(1, "%", 1);
	}
	return (count);
}

// La fonction retourne le nbr de caractères imprimés
