/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 13:01:40 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:29:53 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	ft_export(char **args, t_minir *mini)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i == 1)
		return (basic_export(mini));
	else
	{
		args++;
		while (*args)
		{
			if (!add_on_env(*args, mini))
				args++;
			else
				return (1);
		}
	}
	return (0);
}

int	basic_export(t_minir *mini)
{
	t_listc	*export;
	t_listc	*temp;
	char	*varnname;

	export = sort_listc(mini->env_list);
	while (export)
	{
		if (get_var_cont((char *)export->cont)[0] == '"')
			printf("declare -x %s\n", export->cont);
		else
		{
			varnname = get_var_name(export->cont);
			printf("declare -x %s=\"%s\"\n",
				varnname,
				get_var_cont(export->cont));
			free(varnname);
		}
		temp = export;
		export = export->next;
		free(temp);
	}
	return (0);
}

int	add_on_env(char *arg, t_minir *mini)
{
	t_listc	*env_list;
	t_listc	*local_list;
	char	*cont;
	int		append;

	append = 0;
	env_list = mini->env_list;
	local_list = mini->local_var;
	cont = arg;
	if (ft_strchr(arg, '=') == NULL)
	{
		if (add_on_env_02(arg, local_list) == 1)
			return (1);
		cont = local_list->cont;
	}
	if (ft_strchr(cont, '+') && ft_strchr(cont, '+')[1] == '=')
		append = 1;
	if (add_on_env_03(cont, env_list, append) == 0)
		return (0);
	if (append)
		ft_lstadd_backc(&(mini->env_list), ft_lstnewc(var_noquot(cont)));
	else
		ft_lstadd_backc(&(mini->env_list), ft_lstnewc(var_noquot(cont)));
	return (0);
}
