/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:48:31 by dde-giov          #+#    #+#             */
/*   Updated: 2023/02/08 12:48:33 by dde-giov         ###   ########.fr       */
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
