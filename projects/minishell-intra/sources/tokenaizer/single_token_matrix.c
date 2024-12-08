/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_token_matrix.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:29:14 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

void	get_arr2(char *s, t_minir *mini, int flag)
{
	if (!s)
		return ;
	if (flag)
		error_dollar(s, mini);
	ft_count_words(s, mini);
	make_matrix(s, mini);
}

char	*get_cmd_token(char *s, t_minir *mini)
{
	int	i;
	int	flag;

	i = 0;
	if (s[i] == '\'')
	{
		i++;
		if (s[i] == '\'')
			return (NULL);
		flag = 1;
		return (ft_write_word(s, mini, flag, i));
	}
	else if (s[i] == '"')
	{
		i++;
		if (s[i] == '"')
			return (NULL);
		flag = 2;
		return (ft_write_word(s, mini, flag, i));
	}
	else
	{
		flag = 0;
		return (ft_write_word(s, mini, flag, i));
	}
}

void	make_matrix(char *s, t_minir *mini)
{
	mini->i_flag_dol = 0;
	mini->x2 = 0;
	mini->y2 = 0;
	mini->arr2 = malloc((mini->count_words + 1) * sizeof(char *));
	mini->arr2[mini->count_words] = NULL;
	if (!mini->arr2)
		return ;
	while (mini->y2 < mini->count_words)
	{
		mini->x2 = 0;
		while (*s == ' ')
			s++;
		s = get_cmd_token(s, mini);
		if (mini->arr2[mini->y2] == 0 && mini->y2 < mini->count_words)
		{
			s = NULL;
			return ;
		}
		mini->y2++;
	}
	if (mini->nb_dol > 0)
	{
		free(mini->flag_dol);
		free(mini->save_node_id);
	}
}
