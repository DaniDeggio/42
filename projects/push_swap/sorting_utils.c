/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deggio <deggio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 18:48:06 by dde-giov          #+#    #+#             */
/*   Updated: 2023/10/09 23:38:54 by deggio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	moves_make_counta(t_stack *stk, int n, int i, char c)
{
	int	pos;

	stk->moves = 0;
	pos = find_pos(stk->b, stk->len_b, n, 'a');
	if (pos <= stk->half_b && i <= stk->half_a)
	{
		while (pos > 0 && i > 0)
		{
			rr_move(stk, c);
			pos--;
			i--;
		}
	}
	else if (pos > stk->half_b && i > stk->half_a)
	{
		while (pos < stk->len_b && i < stk->len_a)
		{
			rrr_move(stk, c);
			pos++;
			i++;
		}
	}
	other_case(stk, pos, i, c);
	pb_move(stk, c);
	return (stk->moves);
}

void	other_case(t_stack *stk, int pos, int i, char c)
{
	if (pos > stk->half_b)
	{
		while (pos++ < stk->len_b)
			rrb_move(stk, c);
	}
	else
	{
		while (pos-- > 0)
			rb_move(stk, c);
	}
	if (i > stk->half_a)
	{
		while (i++ < stk->len_a)
			rra_move(stk, c);
	}
	else
	{
		while (i-- > 0)
			ra_move(stk, c);
	}
}

int	moves_make_countb(t_stack *stk, int n, int i, char c)
{
	int	pos;

	stk->moves = 0;
	pos = find_pos(stk->a, stk->len_a, n, 'b');
	if (pos <= stk->half_a && i <= stk->half_b)
	{
		while (pos > 0 && i > 0)
		{
			rr_move(stk, c);
			pos--;
			i--;
		}
	}
	else if (pos > stk->half_a && i > stk->half_b)
	{
		while (pos < stk->len_a && i < stk->len_b)
		{
			rrr_move(stk, c);
			pos++;
			i++;
		}
	}
	other_caseb(stk, pos, i, c);
	pa_move(stk, c);
	return (stk->moves);
}

void	other_caseb(t_stack *stk, int pos, int i, char c)
{
	if (pos > stk->half_a)
	{
		while (pos++ < stk->len_a)
			rra_move(stk, c);
	}
	else
	{
		while (pos-- > 0)
			ra_move(stk, c);
	}
	if (i > stk->half_b)
	{
		while (i++ < stk->len_b)
			rrb_move(stk, c);
	}
	else
	{
		while (i-- > 0)
			rb_move(stk, c);
	}
}

void	frist_small(t_stack *stk)
{
	int	i;

	i = find_min_max(stk->a, stk->len_a, 'b');
	if (i > stk->half_a)
	{
		while (i++ < stk->len_a)
			rra_move(stk, 'm');
	}
	else
	{
		while (i-- > 0)
			ra_move(stk, 'm');
	}
}
