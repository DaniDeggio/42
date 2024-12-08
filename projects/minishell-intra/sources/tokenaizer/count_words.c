/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:30:45 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	check_single_quotes(char *s, int len, int i, t_minir *mini)
{
	mini->count_words++;
	i++;
	if (s[i] == '\'' && (s[i + 1] == ' ' || !s[i + 1]))
		return (i + 1);
	while (i <= len && s[i] != '\'')
		i++;
	return (++i);
}

int	check_no_space(char *s, int len, int i, t_minir *mini)
{
	mini->count_words++;
	while (i <= len && s[i] != ' ')
		i++;
	return (++i);
}

int	check_special(int i, t_minir *mini)
{
	mini->count_words++;
	i += 2;
	return (i);
}

void	ft_count_words(char *s, t_minir *mini)
{
	int	len;
	int	i;

	i = 0;
	mini->count_words = 0;
	len = ft_strlen(s) - 1;
	while (i <= len)
	{
		if (s[i] == '\'')
			i = check_single_quotes(s, len, i, mini);
		else if (s[i] == '"')
			i = check_dble_quotes(s, len, i, mini);
		else if (s[i] != ' ')
			i = check_no_space(s, len, i, mini);
		else
			i++;
	}
}

int	check_dble_quotes(char *s, int len, int i, t_minir *mini)
{
	mini->count_words++;
	i++;
	if (s[i] == '"' && (s[i + 1] == ' ' || !s[i + 1]))
		return (i + 1);
	while (i <= len && s[i] != '"')
	{
		if (s[i] == '\\' && s[i + 1] == '"')
			i += 2;
		else
			i++;
	}
	return (++i);
}
