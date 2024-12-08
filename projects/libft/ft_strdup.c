/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 16:35:24 by dde-giov          #+#    #+#             */
/*   Updated: 2023/01/28 18:49:44 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

char	*ft_strdup(const char *s)
{
	size_t	sdim;
	char	*snew;

	sdim = ft_strlen(s) + 1;
	snew = (char *)malloc(sdim);
	if (snew)
		ft_memcpy(snew, s, sdim);
	else
		return (NULL);
	return (snew);
}
