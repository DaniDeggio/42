/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 17:11:06 by dde-giov          #+#    #+#             */
/*   Updated: 2023/02/08 12:45:48 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static int	ft_len_int(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
	{
		len += 1;
		n = -n - 1;
	}
	if (n < 0)
	{
		len += 1;
		n = -n;
	}
	if (n > 0)
	{
		while (n > 0)
		{
			n /= 10;
			len++;
		}
	}
	return (len);
}

static char	*ft_converter(int n, int len, char *converted)
{
	int	t;

	converted[len--] = '\0';
	if (n < 0)
	{
		n = -n;
		converted[0] = '-';
	}
	if (n == 0)
		converted[len] = '0';
	if (n > 0)
	{
		while (n > 9)
		{
			t = n % 10;
			n /= 10;
			converted[len--] = t + 48;
		}
		converted[len] = n + 48;
	}
	return (converted);
}

static char	*ft_min_int(int n, int len, char *minconverted)
{
	int	f;
	int	t;

	n = -n -1;
	minconverted[0] = '-';
	minconverted[len--] = '\0';
	t = 0;
	f = 0;
	if (n > 0)
	{
		if (n > 9 && f == 0)
			t = n % 10;
			n /= 10;
			minconverted[len--] = t + 49;
			f = 1;
		while (n > 9)
		{
			t = n % 10;
			n /= 10;
			minconverted[len--] = t + 48;
		}
		minconverted[len] = n + 48;
	}
	return (minconverted);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*itoed;

	len = ft_len_int(n);
	itoed = (char *)malloc((len + 1) * sizeof(char));
	if (!itoed)
		return (NULL);
	if (n == -2147483648)
	{
		itoed = ft_min_int(n, (len), itoed);
		return (itoed);
	}
	itoed = ft_converter(n, (len), itoed);
	return (itoed);
}
