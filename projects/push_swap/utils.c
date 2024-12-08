/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 17:10:18 by dde-giov          #+#    #+#             */
/*   Updated: 2023/11/06 17:04:21 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_exit(int i, t_stack *stk)
{
	if (i == 1 || i == 2)
		write(2, "Error\n", 6);
	if (i != 3 && i != 2)
	{
		free(stk->a);
		free(stk->b);
	}
	if (i != 3)
		free(stk);
	if (i != 9)
		exit(1);
}

int	check_stk(t_stack *stack, int *stk, int i, int len)
{
	int	check;

	check = 0;
	if (i > len - 2)
		return (check);
	if (stk[i] < stk[i + 1])
		check = check_stk(stack, stk, i + 1, len);
	else
		check += 1;
	return (check);
}

void	free_tmp(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i] != NULL)
		free(tmp[i++]);
	free(tmp);
}

void	check_max(t_stack *stk, char **tmp, int i)
{
	if (ft_atoi(tmp[i]) > 2147483647
		|| ft_atoi(tmp[i]) < -2147483648)
	{
		i--;
		while (tmp[++i] != NULL)
			free(tmp[i]);
		free(tmp);
		ft_exit(1, stk);
	}
}
