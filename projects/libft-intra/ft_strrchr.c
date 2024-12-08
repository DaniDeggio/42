/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:56:41 by dde-giov          #+#    #+#             */
/*   Updated: 2023/02/08 12:49:27 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

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
