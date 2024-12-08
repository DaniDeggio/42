/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:28:59 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

char	*get_var_name(char *full_var)
{
	char	*name;
	char	*p;
	int		var_name_length;

	p = ft_strchr(full_var, '=');
	if (!p)
		return (full_var);
	var_name_length = ft_strlen(full_var) - ft_strlen(p);
	if (full_var[var_name_length - 1] == '+')
	{
		var_name_length--;
		p--;
	}
	name = malloc(sizeof(char) * var_name_length + 1);
	name[var_name_length] = '\0';
	ft_strncpy(name, full_var, p - full_var);
	return (name);
}

t_listc	*copy_env_in_list(char **env)
{
	t_listc	*head;

	head = ft_lstnewc((void *)ft_strdup(*env));
	env++;
	while (*env)
	{
		ft_lstadd_backc(&head, ft_lstnewc(ft_strdup(*env)));
		env++;
	}
	return (head);
}

void	insert_between_node(t_listc *prev, char *cont)
{
	t_listc	*new_node;

	new_node = (t_listc *)malloc(sizeof(t_listc));
	new_node->cont = cont;
	new_node->next = prev->next;
	prev->next = new_node;
}

t_listc	*insert_sorted(t_listc *sorted_list,
			t_listc *new_node, int var_name_length)
{
	t_listc	*prev;
	t_listc	*current;

	prev = NULL;
	current = sorted_list;
	while (current && ft_strncmp(new_node->cont,
			current->cont, var_name_length) > 0)
	{
		prev = current;
		current = current->next;
	}
	if (prev == NULL)
	{
		new_node->next = sorted_list;
		return (new_node);
	}
	else
	{
		new_node->next = prev->next;
		prev->next = new_node;
		return (sorted_list);
	}
}

t_listc	*sort_listc(t_listc *list)
{
	t_listc	*tmp_list;
	t_listc	*sorted_list;
	t_listc	*new_node;

	sorted_list = NULL;
	tmp_list = list;
	while (tmp_list)
	{
		new_node = ft_lstnewc(tmp_list->cont);
		sorted_list = insert_sorted(sorted_list, new_node,
				var_name_length(tmp_list->cont));
		tmp_list = tmp_list->next;
	}
	return (sorted_list);
}
