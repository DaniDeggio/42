/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:55:54 by dde-giov          #+#    #+#             */
/*   Updated: 2023/11/06 17:04:35 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_check_tmp(char **tmp, int i)
{
	int	j;

	while (tmp[i] != 0)
	{
		if ((ft_isdigit(tmp[i][0]) == 0 && (tmp[i][0] != '-'
			|| tmp[i][0] == '+')) || ((tmp[i][0] == '-' || tmp[i][0] == '+')
			&& (tmp[i][1] == '\0' || tmp[i][1] == '0')))
			return (-1);
		j = 1;
		while (tmp[i][j] != '\0')
		{
			if (ft_isdigit(tmp[i][j]) == 0)
				return (-1);
			j++;
		}
		j = 0;
		while (j < i)
		{
			if (ft_strcmp(tmp[i], tmp[j]) == 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (i);
}

int	ft_check_stack(t_stack *stk)
{
	int	i;
	int	j;

	i = 0;
	while (i < stk->len_a)
	{
		j = 0;
		while (j < stk->len_a)
		{
			if (stk->a[i] == stk->a[j] && i != j)
				ft_exit(1, stk);
			j++;
		}
		i++;
	}
	return (0);
}

void	singleav(char **av, t_stack *stack)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = ft_split(av[1], ' ');
	if (tmp == NULL)
	{
		free(tmp);
		ft_exit(1, stack);
	}
	stack->len_a = ft_check_tmp(tmp, 0);
	if (stack->len_a == -1)
	{
		free_tmp(tmp);
		ft_exit(2, stack);
	}
	stack->a = malloc(sizeof(int) * stack->len_a);
	stack->b = malloc(sizeof(int) * stack->len_a);
	while (++i < stack->len_a)
	{
		check_max(stack, tmp, i);
		stack->a[i] = (int)ft_atoi(tmp[i]);
		free(tmp[i]);
	}
	free(tmp);
}

void	multipleav(int ac, char **av, t_stack *stack)
{
	int	i;

	i = 0;
	stack->len_a = ac - 1;
	stack->len_b = 0;
	stack->a = malloc(sizeof(int) * stack->len_a);
	stack->b = malloc(sizeof(int) * stack->len_a);
	if (stack->a == NULL || stack->b == NULL)
		ft_exit(0, stack);
	if (ft_check_tmp(av, 1) == -1)
		ft_exit(1, stack);
	while (i < stack->len_a)
	{
		if (ft_atoi(av[i + 1]) > 2147483647
			|| ft_atoi(av[i + 1]) < -2147483648)
			ft_exit(1, stack);
		stack->a[i] = (int)ft_atoi(av[i + 1]);
		i++;
	}
}
