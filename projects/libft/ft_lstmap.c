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

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*list_ptr;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		list_ptr = ft_lstnew(f(lst->content));
		if (!list_ptr)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, list_ptr);
		lst = lst->next;
	}
	return (new_list);
}
