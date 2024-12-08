/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:29:21 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

void	init_splitarr(char *s, t_minir *mini)
{
	if (!s)
		return ;
	mini->nb_tokens = 0;
	mini->split_arr = NULL;
	count_tokens(s, mini);
	create_array(s, mini);
}

int	process_special_token(t_minir *mini, char *s, int i)
{
	if (s[i] == '|' || s[i] == '>' || s[i] == '<')
	{
		mini->nb_tokens++;
		if (s[i] == '|')
			return (++i);
		else if (s[i] == '<' && s[i + 1] == '<')
			return (i + 2);
		else if (s[i] == '>' && s[i + 1] != '>')
			return (++i);
		else if (s[i] == '>' && s[i + 1] == '>')
			return (i + 2);
		else
			return (++i);
	}
	else
		return (++i);
}

int	check_s_d_quotes(char *s, int i)
{
	if (s[i] == '"')
	{
		i++;
		while (s[i] != '"' && s[i])
			i++;
	}
	else if (s[i] == '\'')
	{
		i++;
		while (s[i] != '\'' && s[i])
			i++;
	}
	return (i);
}

int	count_tokens(char *s, t_minir *mini)
{
	int		i;
	int		len;

	if (!s)
		return (0);
	i = 0;
	len = ft_strlen(s) - 1;
	while (i <= len)
	{
		if (s[i] != ' ' && s[i] != '|' && s[i] != '<' && s[i] != '>')
		{
			mini->nb_tokens++;
			while (i <= len && (s[i] != '|' && s[i] != '<' && s[i] != '>'))
			{
				if (s[i] == '\'' || s[i] == '"')
					i = check_s_d_quotes(s, i);
				i++;
			}
		}
		if (s[i] == ' ')
			i++;
		else
			i = process_special_token(mini, s, i);
	}
	return (mini->nb_tokens);
}
