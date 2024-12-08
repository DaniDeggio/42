/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_wrong_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:31:05 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	error_dollar(char *s, t_minir *mini)
{
	int	i;

	if (error_dollar_01(s, mini))
		return (1);
	i = 0;
	while (s[i] && mini->i_flag_dol < mini->nb_dol)
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
				i++;
		}
		else if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1] && s[i +1] != '"')
			i += error_dollar_00(s, i, mini);
		i++;
	}
	return (0);
}

int	error_dollar_00(char *s, int i, t_minir *mini)
{
	if (s[i + 1] == '$')
	{
		mini->flag_dol[mini->i_flag_dol++] = -1;
		mini->flag_dol[mini->i_flag_dol] = -1;
		i += 2;
	}
	else if (error_dollar_02(s, i, mini) == -1)
		mini->flag_dol[mini->i_flag_dol] = -1;
	else
	{
		i += error_dollar_02(s, i, mini);
	}
	mini->i_flag_dol++;
	return (i);
}

int	error_dollar_01(char *s, t_minir *mini)
{
	int	i;

	i = 0;
	if (count_dollar_sign(s, mini) != 0)
	{
		mini->save_node_id = malloc(sizeof(int) * mini->nb_dol);
		mini->flag_dol = malloc(sizeof(int) * mini->nb_dol);
		while (i < mini->nb_dol)
			mini->flag_dol[i++] = 0;
		if (!mini->flag_dol && !mini->save_node_id)
			return (1);
		mini->i_flag_dol = 0;
	}
	return (0);
}
