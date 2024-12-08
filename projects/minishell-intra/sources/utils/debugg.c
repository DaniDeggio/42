/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:28:39 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%d - %s\n", i, array[i]);
		i++;
	}
	printf("end of array\n\n");
}

void	printlist(t_minir *mini)
{
	t_listc	*tmp_list;

	tmp_list = mini->env_list;
	printf("questa è la lista_ENV:\n");
	while (tmp_list != NULL)
	{
		printf("cont: %s\n", tmp_list->cont);
		printf("number: %d\n\n", tmp_list->id);
		tmp_list = tmp_list->next;
	}
}

void	printvar(t_listc *local_var)
{
	t_listc	*head;

	head = local_var;
	printf("questa è la lista:\n");
	while (local_var != NULL)
	{
		printf("cont: %s\n", local_var->cont);
		printf("number: %d\n\n", local_var->id);
		local_var = local_var->next;
	}
	local_var = head;
}
