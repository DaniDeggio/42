/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 12:46:19 by dde-giov          #+#    #+#             */
/*   Updated: 2023/02/08 12:46:19 by dde-giov         ###   ########.fr       */
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
