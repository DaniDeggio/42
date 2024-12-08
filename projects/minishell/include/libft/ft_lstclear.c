/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:50:39 by dde-giov          #+#    #+#             */
/*   Updated: 2023/01/28 18:26:56 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;
	t_list	*element;

	if (!lst || !del)
		return ;
	element = *lst;
	while (element)
	{
		next = element->next;
		if (element->content)
			del(element->content);
		free(element);
		element = next;
	}
	*lst = NULL;
}
