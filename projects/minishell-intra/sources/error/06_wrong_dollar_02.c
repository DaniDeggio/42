/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_wrong_dollar_02.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:29:55 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	count_dollar_sign(char *s, t_minir *mini)
{
	int	i;

	i = 0;
	mini->nb_dol = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1] && s[i + 1] != '"')
			mini->nb_dol++;
		i++;
	}
	return (mini->nb_dol);
}

int	check_local_list(char *check_envp, t_minir *mini, int len)
{
	t_listc	*tmp_list;

	tmp_list = mini->local_var;
	while (tmp_list != NULL)
	{
		if (!ft_strncmp(check_envp, tmp_list->cont, len))
			return (0);
		tmp_list = tmp_list->next;
		mini->y_mx_envp++;
	}
	return (-1);
}

int	error_dollar_03(char *check_envp, t_minir *mini, int len)
{
	t_listc	*tmp_list;

	tmp_list = mini->env_list;
	mini->y_mx_envp = 0;
	while (tmp_list != NULL)
	{
		if (!ft_strncmp(check_envp, tmp_list->cont, len))
			return (0);
		if (!ft_strncmp(check_envp, "?", 1))
			return (0);
		tmp_list = tmp_list->next;
		mini->y_mx_envp++;
	}
	mini->y_mx_envp = 0;
	if (!check_local_list(check_envp, mini, len))
		return (0);
	return (1);
}
