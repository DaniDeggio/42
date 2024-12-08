/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:28:35 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

void	ft_lstadd_backc(t_listc **lst, t_listc *new)
{
	t_listc	*temp;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		temp = ft_lstlastc(*lst);
		temp->next = new;
	}
}

t_listc	*ft_lstnewc(void *cont)
{
	t_listc	*new_node;

	new_node = (t_listc *)malloc(sizeof(t_listc));
	if (!new_node)
		return (NULL);
	new_node->next = NULL;
	new_node->cont = cont;
	return (new_node);
}

t_listc	*ft_lstlastc(t_listc *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

int	ft_lstsizec(t_listc *lst)
{
	int		i;
	t_listc	*temp;

	i = 0;
	temp = lst;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
