/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:28:47 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

void	envp_to_matrix(t_minir *mini)
{
	t_listc	*tmp_list;
	int		i;

	tmp_list = mini->env_list;
	i = 0;
	mini->env = malloc(sizeof(char *) * (ft_lstsizec(tmp_list) + 1));
	tmp_list = mini->env_list;
	while (tmp_list)
	{
		mini->env[i] = ft_strdup(tmp_list->cont);
		tmp_list = tmp_list->next;
		i++;
	}
	mini->env[i] = NULL;
}

int	matrix_len(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		i++;
	return (i);
}

int	ft_isspace(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' || s[i] == '\t' || s[i] == '\r'
			|| s[i] == '\f' || s[i] == '\f' || s[i] == '\n')
			i++;
		else
			return (1);
	}
	return (0);
}
