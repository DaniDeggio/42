/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:18:02 by dde-giov          #+#    #+#             */
/*   Updated: 2023/02/08 12:45:22 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb > 0 && size > 2147483647 / nmemb)
		return (0);
	ptr = (void *)malloc(nmemb * size);
	if (!(ptr))
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}
