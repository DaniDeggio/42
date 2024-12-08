/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_r.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:54:52 by dde-giov          #+#    #+#             */
/*   Updated: 2023/10/12 19:54:55 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ra_move(t_stack *stack, char c)
{
	int	i;
	int	tmp;

	if (stack->len_a < 2)
		return ;
	if (c == 'm' || c == 'C')
	{
		tmp = stack->a[0];
		i = 0;
		while (i < stack->len_a - 1)
		{
			stack->a[i] = stack->a[i + 1];
			i++;
		}
		stack->a[stack->len_a - 1] = tmp;
	}
	if (c == 'm')
		ft_printf("ra\n");
	stack->moves++;
}

void	rb_move(t_stack *stack, char c)
{
	int	i;
	int	tmp;

	if (stack->len_b < 2)
		return ;
	if (c == 'm' || c == 'C')
	{
		tmp = stack->b[0];
		i = 0;
		while (i < stack->len_b - 1)
		{
			stack->b[i] = stack->b[i + 1];
			i++;
		}
		stack->b[stack->len_b - 1] = tmp;
	}
	if (c == 'm')
		ft_printf("rb\n");
	stack->moves++;
}

void	rr_move(t_stack *stack, char c)
{
	int	i;
	int	j;
	int	tmp;

	if (stack->len_a >= 2 && (c == 'm' || c == 'C'))
	{
		tmp = stack->a[0];
		i = 0;
		j = 1;
		while (i < stack->len_a - 1)
			stack->a[i++] = stack->a[j++];
		stack->a[stack->len_a - 1] = tmp;
	}
	if (stack->len_a >= 2 && (c == 'm' || c == 'C'))
	{
		tmp = stack->b[0];
		i = 0;
		j = 1;
		while (i < stack->len_b - 1)
			stack->b[i++] = stack->b[j++];
		stack->b[stack->len_b - 1] = tmp;
	}
	if (c == 'm')
		ft_printf("rr\n");
	stack->moves++;
}
