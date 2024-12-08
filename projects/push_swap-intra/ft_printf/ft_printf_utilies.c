/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utilies.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 00:47:20 by dde-giov          #+#    #+#             */
/*   Updated: 2023/02/08 00:47:20 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

size_t	ft_printstr(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (ft_printstr("(null)"));
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

size_t	ft_printpointer(void *ptr)
{
	size_t	i;

	i = ft_printstr("0x");
	i += ft_printhex((unsigned long)ptr, 'x');
	return (i);
}

size_t	ft_printnbr(int nbr)
{
	size_t	i;

	i = 0;
	if (nbr == -2147483648)
		return (ft_printstr("-2147483648"));
	if (nbr < 0)
	{
		write(1, "-", 1);
		i++;
		nbr *= -1;
	}
	if (nbr > 9)
		i += ft_printnbr(nbr / 10);
	ft_printchar((nbr % 10) + 48);
	return (i + 1);
}

size_t	ft_printunbr(unsigned int nbr)
{
	size_t	i;

	i = 0;
	if (nbr > 9)
		i += ft_printunbr(nbr / 10);
	ft_printchar((nbr % 10) + 48);
	return (i + 1);
}

size_t	ft_printhex(size_t nbr, char c)
{
	size_t	i;

	i = 0;
	if (nbr > 15)
		i += ft_printhex(nbr / 16, c);
	if (c == 'x')
		i += ft_printchar("0123456789abcdef"[nbr % 16]);
	else if (c == 'X')
		i += ft_printchar("0123456789ABCDEF"[nbr % 16]);
	return (i);
}
