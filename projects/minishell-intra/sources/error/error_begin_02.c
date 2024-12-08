/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_begin_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:29:32 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	error_begin_02(char *s, t_minir *mini)
{
	int	i;

	i = 0;
	while (!(*s > 32 && *s < 127))
		s++;
	if (s[i] == '>' || s[i] == '<')
	{
		if ((s[i] == '>' && s[i + 1] == '>')
			|| (s[i] == '<' && s[i + 1] == '<'))
		{
			s += 2;
			if (check_next_chars(s, mini))
				return (1);
		}
		else
		{
			s++;
			if (check_next_chars(s, mini))
				return (1);
		}
	}
	return (0);
}

int	check_next_chars(char *s, t_minir *mini)
{
	if (ft_isspace(s) == 0)
		return (return_nl_error(mini));
	else
		return (0);
}
