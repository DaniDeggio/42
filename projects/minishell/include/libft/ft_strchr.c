/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 14:56:41 by dde-giov          #+#    #+#             */
/*   Updated: 2023/01/31 22:19:11 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

char	*ft_strchr( const char *str, int character )
{
	while (*str != '\0' && (char)character != *str)
	{
		str++;
	}
	if (*str == (char)character)
	{
		return ((char *) str);
	}
	return (0);
}
