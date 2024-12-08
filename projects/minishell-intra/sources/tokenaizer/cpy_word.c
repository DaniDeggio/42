/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:30:50 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	copy_no_quotes(char *s, int i, t_minir *mini, int len_name_var)
{
	while (s[i] != ' ' && s[i])
	{
		if (s[i] == '$' && s[i + 1] == '?')
			i = copy_exit_code(mini, i);
		else if (s[i] == '$' && s[i + 1] == '$')
			i += copy_dble_dollar(i, mini);
		else if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1])
		{
			i++;
			if (mini->flag_dol[mini->i_flag_dol] == 0)
			{
				len_name_var = ft_strlen_name_var(s, &i, len_name_var);
				copy_expanded_str(mini, len_name_var);
			}
			else
			{
				while (s[i] != '"' && s[i] != ' ' && s[i] != '$' && s[i])
					i++;
			}
			mini->i_flag_dol++;
		}
		else
			mini->arr2[mini->y2][mini->x2++] = s[i++];
	}
	return (i);
}

int	copy_dble_qoutes_02(char *s, int i, t_minir *mini, int len_name_var)
{
	i++;
	if (mini->flag_dol[mini->i_flag_dol] == 0)
	{
		len_name_var = ft_strlen_name_var(s, &i, len_name_var);
		copy_expanded_str(mini, len_name_var);
	}
	else
	{
		while (s[i] != '"' && s[i] != ' ' && s[i] != '$' && s[i])
			i++;
	}
	mini->i_flag_dol++;
	return (i);
}

int	copy_dble_quotes(char *s, int i, t_minir *mini, int len_name_var)
{
	while (s[i] != '"')
	{
		if (s[i] == '$' && s[i + 1] == '$')
			i = copy_dble_dollar(i, mini);
		else if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1] && s[i + 1] != '"')
			i = copy_dble_qoutes_02(s, i, mini, len_name_var);
		else if (s[i] == '$' && s[i + 1] == '?')
			i = copy_exit_code(mini, i);
		else if (s[i] == '\\' && s[i + 1] == '"')
		{
			mini->arr2[mini->y2][mini->x2++] = '"';
			i += 2;
		}
		else
			mini->arr2[mini->y2][mini->x2++] = s[i++];
	}
	return (i);
}

char	*ft_write_word(char *s, t_minir *mini, int flag, int i)
{
	int	len;
	int	len_name_var;

	len_name_var = 0;
	len = ft_strlen_custom(s, flag, mini);
	mini->arr2[mini->y2] = malloc(len + 1);
	if (!mini->arr2[mini->y2])
		return (NULL);
	if (flag == 2)
		i = copy_dble_quotes(s, i, mini, len_name_var);
	else if (flag == 1)
	{
		while (s[i] != '\'')
			mini->arr2[mini->y2][mini->x2++] = s[i++];
	}
	else
	{
		i = copy_no_quotes(s, i, mini, len_name_var);
	}
	mini->arr2[mini->y2][mini->x2] = '\0';
	return (&s[++i]);
}
