/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   localvar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:09:39 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:26:30 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	update_var(char *str, t_listc *list, int add)
{
	t_listc	*tmp;
	char	*temp;

	tmp = list;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->cont, var_name_length(str)))
		{
			if (!add)
			{
				free(tmp->cont);
				tmp->cont = var_noquot(str);
				return (1);
			}
			temp = ft_strjoin(tmp->cont,
					str + var_name_length(str) + 2);
			free(tmp->cont);
			tmp->cont = var_noquot(temp);
			free(temp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	new_var(char *str, t_minir *mini, int add, int empty)
{
	t_listc	*tmp;
	char	*name;
	char	*temp;

	name = get_var_name(str);
	if (add && empty)
	{
		free(str);
		str = ft_strjoin(name, "=");
	}
	else if (add && !empty)
	{
		temp = ft_strjoin(name, str + ft_strlen(name) + 1);
		free(str);
		str = var_noquot(temp);
		free(temp);
	}
	tmp = mini->local_var;
	tmp = ft_lstnewc(var_noquot(str));
	if (!tmp)
		ft_putstr_fd("malloc", 2);
	ft_lstadd_backc(&mini->local_var, tmp);
	free(name);
	return (0);
}

int	add_var(char *str, t_minir *mini)
{
	int		skip;
	int		add;
	int		empty;
	char	*name;

	skip = 0;
	add = 0;
	empty = 0;
	name = get_var_name(str);
	if (str[ft_strlen(name)] == '+')
		add = 1;
	if (!str[ft_strlen(name) + 1] || ((!str[ft_strlen(name) + 2]) && add))
		empty = 1;
	if (update_var(str, mini->local_var, add))
		skip = 1;
	if (update_var(str, mini->env_list, add))
		skip = 1;
	if (!skip)
		new_var(str, mini, add, empty);
	free(name);
	return (0);
}
