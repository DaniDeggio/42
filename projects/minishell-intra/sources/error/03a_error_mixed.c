/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03a_error_mixed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 00:24:33 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:31:02 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	check_extra_char(char *s, int i, t_minir *mini)
{
	char	c;
	char	d;
	char	e;

	if (s[i + 1] == '>' || s[i + 1] == '<')
	{
		if (s[i + 2])
			i += 2;
		else
		{
			return (return_nl_error(mini));
		}
		c = s[i - 2];
		d = s[i - 1];
		e = s[i];
		if (c == '<' && d == '<' && e == '<')
			return (return_not_required(mini));
		else if ((c == '>' && d == '>') || (c == '<' && d == '<'))
		{
			return ((check_extra_char_2(e, mini)));
		}
	}
	return (0);
}

int	check_extra_char_2(char e, t_minir *mini)
{
	if (e == '>')
		return (return_gt_error(mini));
	else if (e == '<')
		return (return_lt_error(mini));
	else if (e == '|')
		return (return_pipe_error(mini));
	return (0);
}

int	check_next_arg(char *s, int i, t_minir *mini)
{
	i++;
	if (s[i] == '>' || s[i] == '<')
		i++;
	while (s[i] == ' ' && s[i] != '\0')
		i++;
	if (s[i] == '\0')
		return (return_not_required(mini));
	if (s[i] != '>' && s[i] != '<' && s[i] != '|')
		return (0);
	else
	{
		if (s[i] == '>')
			return (return_gt_error(mini));
		else if (s[i] == '<')
			return (return_lt_error(mini));
		else
			return (return_pipe_error(mini));
	}
}

int	find_i(char *s, int i)
{
	while (s[i] != '|' && s[i] != '>' && s[i] != '<' && s[i])
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
		i++;
	}
	return (i);
}
