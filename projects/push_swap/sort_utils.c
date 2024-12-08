/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:55:15 by dde-giov          #+#    #+#             */
/*   Updated: 2023/10/12 19:55:17 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	optimize_push(t_stack *stack, int i, char c)
{
	if (i < 2)
	{
		while (i > 0)
		{
			if (c == 'a')
				ra_move(stack, 'm');
			else
				rb_move(stack, 'm');
			i--;
		}
	}
	else
	{
		if (c == 'a')
			while (i++ < stack->len_a)
				rra_move(stack, 'm');
		else
			while (i++ < stack->len_b)
				rrb_move(stack, 'm');
	}
}

void	push_back(t_stack *stk)
{
	int	min_moves;
	int	min_i;
	int	moves;
	int	i;

	while (stk->len_b > 0)
	{
		i = 0;
		min_moves = moves_make_countb(stk, stk->b[0], 0, 'c');
		min_i = 0;
		while (i < stk->len_b)
		{
			moves = moves_make_countb(stk, stk->b[i], i, 'c');
			if (moves < min_moves)
			{
				min_i = i;
				min_moves = moves;
			}
			i++;
		}
		moves_make_countb(stk, stk->b[min_i], min_i, 'm');
	}
}

int	find_min_max(int *stk, int len, char c)
{
	int	i;
	int	tmp;
	int	pos;

	i = 0;
	tmp = stk[0];
	pos = 0;
	while (i < len)
	{
		if (stk[i] < tmp && c == 'b')
		{
			tmp = stk[i];
			pos = i;
		}
		else if (stk[i] > tmp && c == 'a')
		{
			tmp = stk[i];
			pos = i;
		}
		i++;
	}
	return (pos);
}

int	find_pos(int *stk, int len, int n, char c)
{
	int	i;

	i = 0;
	while (i < len - 1)
	{
		if (stk[i] > n && stk[i + 1] < n && c == 'a')
			return (i + 1);
		else if (stk[i] < n && stk[i + 1] > n && c == 'b')
			return (i + 1);
		i++;
	}
	if (n > stk[0] && n < stk[len - 1] && c == 'a')
		return (0);
	else if (n < stk[0] && n > stk[len - 1] && c == 'b')
		return (0);
	return (find_min_max(stk, len, c));
}

void	find_middle(t_stack *stk)
{
	if ((stk->len_a) % 2 == 0)
		stk->half_a = ((stk->len_a) / 2);
	else
		stk->half_a = (((stk->len_a) / 2) + 1);
	if ((stk->len_b) % 2 == 0)
		stk->half_b = ((stk->len_b) / 2);
	else if ((stk->len_b) % 2 == 1)
		stk->half_b = (((stk->len_b) / 2) + 1);
}
