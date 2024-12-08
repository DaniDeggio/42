/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:55:36 by dde-giov          #+#    #+#             */
/*   Updated: 2023/10/12 19:55:38 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	sorting(t_stack *stack)
{
	if (check_stk(stack, stack->a, 0, stack->len_a) == 0)
		return (0);
	if (stack->len_a == 2)
	{
		sa_move(stack, 'm');
		return (0);
	}
	if (stack->len_a == 3)
		sort_three(stack, stack->a);
	else if (stack->len_a == 5)
		sort_five(stack, stack->a);
	else
	{
		pb_move(stack, 'm');
		pb_move(stack, 'm');
		sort_hundred(stack);
		if (stack->len_a == 3)
			sort_three(stack, stack->a);
		push_back(stack);
		frist_small(stack);
	}
	return (0);
}

void	sort_three(t_stack *stack, int *stk)
{
	if (check_stk(stack, stk, 0, 3) == 0)
		return ;
	if (stk[1] < stk[0] && stk[1] < stk[2])
	{
		if (stk[0] < stk[2])
			sa_move(stack, 'm');
		else
			ra_move(stack, 'm');
	}
	else
	{
		if (stk[2] < stk[0] && stk[0] < stk[1])
			rra_move(stack, 'm');
		else
		{
			sa_move(stack, 'm');
			if (stk[1] < stk[0] && stk[1] < stk[2])
				ra_move(stack, 'm');
			else
				rra_move(stack, 'm');
		}
	}
}

void	sort_five(t_stack *stack, int *stk)
{
	int	i;

	i = find_min_max(stk, stack->len_a, 'b');
	optimize_push(stack, i, 'a');
	pb_move(stack, 'm');
	i = find_min_max(stk, stack->len_a, 'a');
	optimize_push(stack, i, 'a');
	pb_move(stack, 'm');
	sort_three(stack, stk);
	pa_move(stack, 'm');
	ra_move(stack, 'm');
	pa_move(stack, 'm');
}

void	sort_hundred(t_stack *stk)
{
	int	min_moves;
	int	min_i;
	int	moves;
	int	i;

	while (stk->len_a > 3)
	{
		i = 0;
		min_moves = moves_make_counta(stk, stk->a[0], 0, 'c');
		min_i = 0;
		if (check_stk(stk, stk->a, 0, stk->len_a) == 0)
			break ;
		while (i < stk->len_a)
		{
			moves = moves_make_counta(stk, stk->a[i], i, 'c');
			if (moves < min_moves)
			{
				min_moves = moves;
				min_i = i;
			}
			i++;
		}
		moves_make_counta(stk, stk->a[min_i], min_i, 'm');
	}
}
