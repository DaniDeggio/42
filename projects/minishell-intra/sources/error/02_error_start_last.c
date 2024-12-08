/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_error_start_last.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:29:45 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	error_begin(char *str, t_minir *mini)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] == ' ')
		i++;
	if (str[i] == '|' || (str[i] == '<' && str[i + 1] == '|'))
		return (return_pipe_error(mini));
	else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '|')
		return (return_pipe_error(mini));
	else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '|')
		return (return_pipe_error(mini));
	else if (str[i] == '<' && str[i + 1] == '>' && str[i + 2] == '|')
		return (return_pipe_error(mini));
	else if (str[i] == '>' && str[i + 1] == '|')
		return (return_not_required(mini));
	else if (str[i] == '<' && str[i + 1] == '<' && str[i + 2] == '<')
		return (return_not_required(mini));
	else if (str[i] == '>' && str[i + 1] == '<' && str[i + 2] == '|')
		return (return_lt_error(mini));
	else if (str[i] == '>' && str[i + 1] == '>' && str[i + 2] == '>')
		return (return_gt_error(mini));
	return (0);
}

int	error_end(char *s, char c, t_minir *mini)
{
	int	len;

	len = ft_strlen(s);
	if (len == 0)
		return (0);
	while (s[len] == ' ' || s[len] == '\0')
		len--;
	if (s[len] == c)
	{
		if (c != '|')
			return (return_nl_error(mini));
		else
			return (return_not_required(mini));
	}
	return (0);
}
