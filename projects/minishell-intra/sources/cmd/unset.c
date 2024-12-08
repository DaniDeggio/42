/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:32:12 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:29:50 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

void	ft_remove_node(t_listc **list, char *arg)
{
	t_listc	*tmp;
	t_listc	*prev;

	tmp = *list;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(arg, (char *)tmp->cont, ft_strlen(arg)) == 0)
		{
			if (prev == NULL)
				*list = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->cont);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_unset(char **args, t_minir *mini)
{
	int	i;

	i = 1;
	while (args[i])
	{
		ft_remove_node(&(mini->env_list), args[i]);
		ft_remove_node(&(mini->local_var), args[i]);
		i++;
	}
	return (0);
}
