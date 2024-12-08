/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_rr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:55:24 by dde-giov          #+#    #+#             */
/*   Updated: 2023/10/12 19:55:26 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra_move(t_stack *stack, char c)
{
	int	i;
	int	tmp;

	if (stack->len_a < 2)
		return ;
	if (c == 'm' || c == 'C')
	{
		i = stack->len_a - 1;
		tmp = stack->a[i];
		while (i > 0)
		{
			stack->a[i] = stack->a[i - 1];
			i--;
		}
		stack->a[0] = tmp;
	}
	if (c == 'm')
		ft_printf("rra\n");
	stack->moves++;
}

void	rrb_move(t_stack *stack, char c)
{
	int	i;
	int	tmp;

	if (stack->len_a < 2)
		return ;
	if (c == 'm' || c == 'C')
	{
		tmp = stack->b[stack->len_b - 1];
		i = stack->len_b - 1;
		while (i > 0)
		{
			stack->b[i] = stack->b[i - 1];
			i--;
		}
		stack->b[0] = tmp;
	}
	if (c == 'm')
		ft_printf("rrb\n");
	stack->moves++;
}

void	rrr_move(t_stack *stack, char c)
{
	int	i;
	int	j;
	int	tmp;

	if (stack->len_a >= 2 && (c == 'm' || c == 'C'))
	{
		i = stack->len_a - 1;
		j = i - 1;
		tmp = stack->a[i];
		while (i > 0)
			stack->a[i--] = stack->a[j--];
		stack->a[0] = tmp;
	}
	if (stack->len_b >= 2 && (c == 'm' || c == 'C'))
	{
		tmp = stack->b[stack->len_b - 1];
		i = stack->len_b - 1;
		j = i - 1;
		while (i > 0)
			stack->b[i--] = stack->b[j--];
		stack->b[0] = tmp;
	}
	if (c == 'm')
		ft_printf("rrr\n");
	stack->moves++;
}
