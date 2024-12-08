/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_custom.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:29:24 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	ft_strlen_custom(char *s, int flag, t_minir *mini)
{
	int	save_dol;

	save_dol = 0;
	mini->mem_space = 0;
	mini->i = 0;
	if (!s)
		return (0);
	save_dol = mini->i_flag_dol;
	if (flag == 0)
		ft_strlen_no_quotes(s, mini);
	if (flag == 1)
	{
		mini->i++;
		while (s[mini->i] != '\'')
		{
			mini->mem_space++;
			mini->i++;
		}
	}
	if (flag == 2)
		ft_strlen_dble_quotes(s, mini);
	mini->i_flag_dol = save_dol;
	return (mini->mem_space);
}

void	dble_dollar(t_minir *mini)
{
	mini->mem_space += 2;
	mini->i += 2;
	mini->save_node_id[mini->i_flag_dol++] = -1;
	mini->save_node_id[mini->i_flag_dol++] = -1;
}

void	ft_strlen_no_quotes(char *s, t_minir *mini)
{
	while (s[mini->i] && s[mini->i] != ' ')
	{
		if (s[mini->i] == '$' && s[mini->i + 1] == '$')
			dble_dollar(mini);
		else if (s[mini->i] == '$' && s[mini->i + 1] == '?')
			ft_count_exp_print_error(mini);
		else if (s[mini->i] == '$' && s[mini->i + 1] != ' ' && s[mini->i + 1])
		{
			mini->i++;
			if (mini->flag_dol[mini->i_flag_dol] == 0)
				count_expanded_token(mini, s);
			else
			{
				while (s[mini->i] != '"' && s[mini->i] != ' '
					&& s[mini->i] != '$' && s[mini->i])
					mini->i++;
			}
			mini->i_flag_dol++;
		}
		else
		{
			mini->mem_space++;
			mini->i++;
		}
	}
}

void	ft_strlen_dble_quotes_02(char *s, t_minir *mini)
{
	mini->i++;
	if (mini->flag_dol[mini->i_flag_dol] == 0)
		count_expanded_token(mini, s);
	else
	{
		while (s[mini->i] != '"' && s[mini->i] != ' '
			&& s[mini->i] != '$' && s[mini->i])
			mini->i++;
		mini->save_node_id[mini->i_flag_dol] = -1;
	}
	mini->i_flag_dol++;
}

void	ft_strlen_dble_quotes(char *s, t_minir *mini)
{
	mini->i++;
	while (s[mini->i] != '"')
	{
		if (s[mini->i] == '$' && s[mini->i + 1] == '$')
			dble_dollar(mini);
		else if (s[mini->i] == '$' && s[mini->i + 1] == '?')
			ft_count_exp_print_error(mini);
		else if (s[mini->i] == '$' && s[mini->i + 1] != ' '
			&& s[mini->i + 1] && s[mini->i + 1] != '"')
			ft_strlen_dble_quotes_02(s, mini);
		else
		{
			mini->mem_space++;
			mini->i++;
		}
	}
}
