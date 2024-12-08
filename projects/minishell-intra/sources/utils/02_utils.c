/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:28:54 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	var_name_length(char *full_var)
{
	char	*p;
	int		var_name_length;

	p = ft_strchr(full_var, '=');
	if (p)
		var_name_length = ft_strlen(full_var) - ft_strlen(p);
	else
		var_name_length = ft_strlen(full_var);
	if (full_var[var_name_length - 1] == '+')
		var_name_length--;
	return (var_name_length);
}

char	*removeplus(char *full_var)
{
	char	*name;
	char	*varname;

	varname = get_var_name(full_var);
	name = ft_strjoin(varname, ft_strchr(full_var, '='));
	free(varname);
	return (name);
}

char	*var_noquot(char *str)
{
	char	*new_str;
	char	*tmp;
	char	*var_name;

	var_name = get_var_name(str);
	tmp = ft_strjoin(var_name, "=");
	new_str = ft_strjoin(tmp, get_var_cont(str));
	free(tmp);
	free(var_name);
	return (new_str);
}

char	*get_var_cont(char *full_var)
{
	char	*p;
	int		p_len;

	p = ft_strchr(full_var, '=');
	if (!p)
		return ("");
	p++;
	p_len = ft_strlen(p);
	if (*p == '\"' && p[p_len - 1] == '\"')
	{
		p[p_len - 1] = '\0';
		p++;
	}
	return (p);
}
