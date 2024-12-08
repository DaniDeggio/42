/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 01:14:23 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:30:56 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

void	check_duplicate(t_minir *mini, char *cont)
{
	t_listc	*list;

	list = mini->env_list;
	while (list)
	{
		if (!ft_strncmp(cont,
				(char *)list->cont, var_name_length(cont)))
		{
			list->cont = var_noquot(cont);
			return ;
		}
		list = list->next;
	}
	ft_lstadd_backc(&(mini->env_list), ft_lstnewc(var_noquot(cont)));
}

int	add_on_env_02(char *arg, t_listc *local_list)
{
	while (local_list)
	{
		if (ft_strncmp(arg, (char *)local_list->cont,
				var_name_length(arg)) == 0)
		{
			return (0);
		}
		local_list = local_list->next;
	}
	if (!local_list)
		return (printf("ERROR: var doesn't exist in local_list\n"), 1);
	return (1);
}

int	add_on_env_03(char *cont, t_listc *env_list, int append)
{
	while (env_list)
	{
		if (ft_strncmp(cont, (char *)env_list->cont,
				var_name_length(cont)) == 0)
		{
			if (append)
			{
				env_list->cont = ft_strjoin(env_list->cont,
						get_var_cont(cont));
				return (0);
			}
			env_list->cont = var_noquot(cont);
			return (0);
		}
		env_list = env_list->next;
	}
	return (1);
}
