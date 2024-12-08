/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 22:05:17 by dde-giov          #+#    #+#             */
/*   Updated: 2023/02/07 22:05:17 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <unistd.h>

size_t	ft_printchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_conversions(va_list vlist, const char c)
{
	size_t	len;

	len = 0;
	if (c == 'c')
		len = ft_printchar(va_arg(vlist, int));
	else if (c == 's')
		len = ft_printstr(va_arg(vlist, char *));
	else if (c == 'p')
		len = ft_printpointer(va_arg(vlist, void *));
	else if (c == 'd' || c == 'i')
		len = ft_printnbr(va_arg(vlist, int));
	else if (c == 'u')
		len = ft_printunbr(va_arg(vlist, unsigned int));
	else if (c == 'x' || c == 'X')
		len = ft_printhex(va_arg(vlist, unsigned int), c);
	else if (c == '%')
		len = ft_printchar('%');
	else
		return (0);
	return (len);
}

int	ft_printf(const char *ptr, ...)
{
	size_t	i;
	size_t	len;
	va_list	vlist;

	i = 0;
	len = 0;
	va_start(vlist, ptr);
	while (ptr[i])
	{
		if (ptr[i] == '%' )
		{
			len += ft_conversions(vlist, ptr[i + 1]);
			i++;
		}
		else
			len += ft_printchar(ptr[i]);
		i ++;
	}
	va_end(vlist);
	return (len);
}
