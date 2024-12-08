/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_error_mixed.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:29:42 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	error_mixed_start(char *s, t_minir *mini)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i = find_i(s, i);
		if (s[i] == '>' || s[i] == '<' || s[i] == '|')
		{
			if (check_2nd_char(s, i, mini))
				return (1);
			else if (check_extra_char(s, i, mini))
				return (1);
			else if (check_next_arg(s, i, mini))
				return (1);
			if (s[i + 1] == '>' || s[i + 1] == '<')
				i += 2;
			else
				i++;
			if (check_spaces(s, &i, mini) != 0)
				return (1);
		}
	}
	return (0);
}

int	check_2nd_char_03(char *s, int i, char d, t_minir *mini)
{
	if (d == '>')
		return (return_not_required(mini));
	else if (d == '|')
		return (return_pipe_error(mini));
	else if (d == '<' && s[i + 1] == '<')
		return (return_not_required(mini));
	else if (d == '<' && s[i + 1] == '>')
		return (return_not_required(mini));
	return (0);
}

int	check_2nd_char(char *s, int i, t_minir *mini)
{
	char	c;
	char	d;

	if (s[i + 1])
		i++;
	else
		return (return_nl_error(mini));
	c = s[i - 1];
	d = s[i];
	if (c == '>' && check_2nd_char_02(s, i, d, mini) == 1)
		return (1);
	else if (c == '<' && check_2nd_char_03(s, i, d, mini) == 1)
		return (1);
	else if (c == '|' && (d == '>' || d == '<' || d == '|'))
		return (return_not_required(mini));
	return (0);
}

int	check_spaces(char *s, int *i, t_minir *mini)
{
	while (s[*i] == ' ')
		(*i)++;
	if (s[*i] == '\0')
		return (return_nl_error(mini));
	return (0);
}

int	check_2nd_char_02(char *s, int i, char d, t_minir *mini)
{
	if (d == '<')
		return (return_lt_error(mini));
	else if (d == '|')
		return (return_not_required(mini));
	else if (d == '>' && s[i + 1] == '>')
		return (return_not_required(mini));
	else if (d == '>' && s[i + 1] == '<')
		return (return_not_required(mini));
	return (0);
}
