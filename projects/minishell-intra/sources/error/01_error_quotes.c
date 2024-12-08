/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_error_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:33:49 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:31:00 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	count_quotes(char *s)
{
	if (count_single_quotes(s))
		return (-1);
	if (count_dble_quotes(s))
		return (-1);
	return (0);
}

int	count_single_quotes(char *s)
{
	int	i;
	int	count_quotes;

	count_quotes = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '"' && count_quotes % 2 == 0)
		{
			i++;
			while (s[i] != '"' && s[i])
				i++;
		}
		if (s[i] == '\\' && s[i + 1] == '\'')
			i += 2;
		if (s[i] == '\'')
			count_quotes++;
		i++;
	}
	if (count_quotes % 2 != 0)
	{
		ft_putstr_fd("syntax error: error unclosed quotes\n", 2);
		return (1);
	}
	return (0);
}

int	count_dble_quotes(char *s)
{
	int	i;
	int	count_quotes;

	i = 0;
	count_quotes = 0;
	while (s[i])
	{
		if (s[i] == '\'' && (count_quotes % 2 == 0))
		{
			i++;
			while (s[i] != '\'' && s[i])
				i++;
		}
		else if (s[i] == '\\' && s[i + 1] == '"')
			i += 2;
		if (s[i] == '"')
			count_quotes++;
		i++;
	}
	if (count_quotes % 2 != 0)
	{
		ft_putstr_fd("error unclosed quotes\n", 2);
		return (1);
	}
	return (0);
}
