/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:56:41 by dde-giov          #+#    #+#             */
/*   Updated: 2023/01/31 22:24:54 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

// char	*ft_strrchr(const char *str, int character)
// {
// 	size_t	i;

// 	i = ft_strlen(str);
// 	while (i >= 0)
// 	{
// 		if (str[i] == character)
// 			return ((char *)str + i);
// 		i--;
// 	}
// 	return (0);
// }

char	*ft_strrchr(const char *str, int character)
{
	size_t		i;
	const char	*begin;

	begin = str;
	i = ft_strlen(str);
	str = (str + i);
	while (*str != *begin && (char)character != *str)
		str--;
	if ((char)character == *str)
		return ((char *) str);
	return (0);
}
