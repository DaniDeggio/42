/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05a_wrong_dollar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:29:34 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	error_dollar_02(char *s, int i, t_minir *mini)
{
	int		len;
	char	*check_envp;
	int		j;
	int		start;

	len = 0;
	j = 0;
	i++;
	start = i;
	if (s[i] == '?')
		return (1);
	error_dollar_02_a(s, &i, &len);
	check_envp = malloc(sizeof(char) * len + 2);
	i = start;
	while (j < len)
		check_envp[j++] = s[i++];
	error_dollar_02_b(check_envp, &j, &len, mini);
	if (error_dollar_03(check_envp, mini, len) == 1)
	{
		free(check_envp);
		return (1);
	}
	free(check_envp);
	return (len - 1);
}

void	error_dollar_02_a(char *s, int *i, int *len)
{
	while (s[*i] != '"' && s[*i] != '\'' && s[*i] != ' ' && s[*i])
	{
		(*i)++;
		(*len)++;
		if (s[*i] == '$')
			break ;
	}
}

void	error_dollar_02_b(char *check_envp, int *j, int *len, t_minir *mini)
{
	check_envp[*j] = '=';
	check_envp[*j + 1] = '\0';
	len += 1;
	mini->y_mx_envp = 0;
	mini->xenvp = *len;
}
