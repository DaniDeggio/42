/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:30:52 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	count_expanded_token_02(t_minir *mini)
{
	t_listc	*tmp_list;

	tmp_list = mini->env_list;
	while (tmp_list != NULL)
	{
		if (!ft_strncmp(mini->check_exp, tmp_list->cont, mini->len_call_exp))
		{
			while (tmp_list->cont[mini->xenvp])
			{
				mini->mem_space++;
				mini->xenvp++;
			}
			free(mini->check_exp);
			mini->save_node_id[mini->i_flag_dol] = tmp_list->id;
			return (0);
		}
		tmp_list = tmp_list->next;
		mini->y_mx_envp++;
	}
	mini->y_mx_envp = 0;
	return (-1);
}

void	copy_expanded_str(t_minir *mini, int len_name_var)
{
	t_listc	*tmp_list;

	if (mini->flag_list == 0)
	{
		tmp_list = mini->env_list;
		while (tmp_list && tmp_list->id != mini->save_node_id[mini->i_flag_dol])
			tmp_list = tmp_list->next;
		mini->xenvp = len_name_var + 1;
		while (tmp_list && tmp_list->cont[mini->xenvp])
			mini->arr2[mini->y2][mini->x2++] = tmp_list->cont[mini->xenvp++];
		return ;
	}
	else
	{
		tmp_list = mini->local_var;
		while (tmp_list && tmp_list->id != mini->save_node_id[mini->i_flag_dol])
			tmp_list = tmp_list->next;
		mini->xenvp = len_name_var + 1;
		while (tmp_list && tmp_list->cont[mini->xenvp])
			mini->arr2[mini->y2][mini->x2++] = tmp_list->cont[mini->xenvp++];
		mini->flag_list = 0;
		return ;
	}
}

void	count_expanded_token(t_minir *mini, char *s)
{
	int	start;
	int	j;

	j = 0;
	start = mini->i;
	while (s[mini->i] != '"' && s[mini->i] != ' '
		&& s[mini->i] != '$' && s[mini->i])
		mini->i++;
	mini->len_call_exp = mini->i - start + 1;
	mini->check_exp = malloc(sizeof(char) * mini->len_call_exp + 1);
	mini->i = start;
	while (j < mini->len_call_exp && s[mini->i] != '"'
		&& s[mini->i] != ' ' && s[mini->i] != '$' && s[mini->i])
		mini->check_exp[j++] = s[mini->i++];
	mini->check_exp[j] = '=';
	mini->check_exp[j + 1] = '\0';
	mini->y_mx_envp = 0;
	mini->xenvp = mini->len_call_exp;
	if (count_expanded_token_02(mini) == -1)
	{
		mini->flag_list = 1;
		count_expanded_token_local_var(mini);
	}
	mini->mem_space++;
	return ;
}

void	count_expanded_token_local_var(t_minir *mini)
{
	t_listc	*tmp_list;

	tmp_list = mini->local_var;
	while (mini->local_var != NULL)
	{
		if (!ft_strncmp(mini->check_exp,
				mini->local_var->cont, mini->len_call_exp))
		{
			while (mini->local_var->cont[mini->xenvp])
			{
				mini->mem_space++;
				mini->xenvp++;
			}
			free(mini->check_exp);
			mini->save_node_id[mini->i_flag_dol] = mini->local_var->id;
			mini->local_var = tmp_list;
			return ;
		}
		mini->local_var = mini->local_var->next;
		mini->y_mx_envp++;
	}
}
