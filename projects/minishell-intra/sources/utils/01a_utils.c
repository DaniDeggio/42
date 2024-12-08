/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01a_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:28:57 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

void	add_index_to_env_list(t_minir *mini)
{
	int		i;
	t_listc	*tmp_list;

	tmp_list = mini->env_list;
	i = 0;
	while (tmp_list != NULL)
	{
		tmp_list->id = i;
		i++;
		tmp_list = tmp_list->next;
	}
}

void	add_index_to_local_var(t_minir *mini)
{
	int		i;
	t_listc	*tmp_list;

	tmp_list = mini->local_var;
	i = 0;
	while (mini->local_var != NULL)
	{
		mini->local_var->id = i;
		i++;
		mini->local_var = mini->local_var->next;
	}
	mini->local_var = tmp_list;
}

void	add_index_to_custom_env(t_minir *mini)
{
	int		i;
	t_listc	*tmp_list;

	tmp_list = mini->env_list;
	i = 0;
	while (mini->env_list != NULL)
	{
		mini->env_list->id = i;
		i++;
		mini->env_list = mini->env_list->next;
	}
	mini->env_list = tmp_list;
}
