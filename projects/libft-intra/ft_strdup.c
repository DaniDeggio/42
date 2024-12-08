/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:48:35 by dde-giov          #+#    #+#             */
/*   Updated: 2023/02/08 12:48:37 by dde-giov         ###   ########.fr       */
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
