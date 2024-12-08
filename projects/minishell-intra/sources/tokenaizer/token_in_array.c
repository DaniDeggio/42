/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_in_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:29:11 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

void	create_array(char *s, t_minir *mini)
{
	int	i;

	i = 0;
	mini->split_arr = malloc((mini->nb_tokens + 1) * sizeof(char *));
	mini->split_arr[mini->nb_tokens] = NULL;
	if (!mini->split_arr)
		return ;
	while (i < mini->nb_tokens)
	{
		while (*s == ' ')
			s++;
		mini->split_arr[i] = get_token(s);
		s += ft_strlen(mini->split_arr[i]);
		i++;
	}
}

void	check_next_special_token(char *s, int i, char **token)
{
	if (s[i] == '>' && s[i + 1] == '>')
	{
		*token = malloc(sizeof(char) * 3);
		(*token)[0] = s[i];
		(*token)[1] = s[i + 1];
		(*token)[2] = 0;
	}
	else if (s[i] == '|')
	{
		*token = malloc(sizeof(char) * 2);
		(*token)[0] = s[i];
		(*token)[1] = 0;
	}
	else if (s[i] == '>' && s[i + 1] != '>')
	{
		*token = malloc(sizeof(char) * 2);
		(*token)[0] = s[i];
		(*token)[1] = 0;
	}
}

void	check_next_special_token_02(char *s, int i, char **token)
{
	if (s[i] == '<' && s[i + 1] == '<')
	{
		*token = malloc(sizeof(char) * 3);
		(*token)[0] = s[i];
		(*token)[1] = s[i + 1];
		(*token)[2] = 0;
	}
	else if (s[i] == '<' && s[i + 1] != '<')
	{
		*token = malloc(sizeof(char) * 2);
		(*token)[0] = s[i];
		(*token)[1] = 0;
	}
}

char	*get_token(char *s)
{
	char	*token;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s[j] != '>' && s[j] != '<' && s[j] != '|')
	{
		j += get_token_01(s, j);
		token = malloc(sizeof(char) * (j + 1));
		if (!token)
			return (NULL);
		token[j] = '\0';
		while (i < j)
		{
			token[i] = s[i];
			i++;
		}
	}
	else
	{
		check_next_special_token(s, j, &token);
		check_next_special_token_02(s, j, &token);
	}
	return (token);
}

int	get_token_01(char *s, int j)
{
	while (s[j] != '|' && s[j] != '>' && s[j] != '<' && s[j] != '\0')
	{
		if (s[j] == '"' || s[j] == '\'')
			j = check_s_d_quotes(s, j);
		j++;
	}
	return (j);
}
