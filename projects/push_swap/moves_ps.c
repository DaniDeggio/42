/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_ps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:55:43 by dde-giov          #+#    #+#             */
/*   Updated: 2023/10/12 19:55:45 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa_move(t_stack *stack, char c)
{
	int	tmp;

	if (stack->len_a > 1 && (c == 'm' || c == 'C'))
	{
		tmp = stack->a[0];
		stack->a[0] = stack->a[1];
		stack->a[1] = tmp;
	}
	if (c == 'm')
		ft_printf("sa\n");
	stack->moves++;
}

void	sb_move(t_stack *stack, char c)
{
	int	tmp;

	if (stack->len_b > 1 && (c == 'm' || c == 'C'))
	{
		tmp = stack->a[0];
		stack->b[0] = stack->b[1];
		stack->b[1] = tmp;
	}
	if (c == 'm')
		ft_printf("sb\n");
	stack->moves++;
}

void	ss_move(t_stack *stack, char c)
{
	if (c == 'm' || c == 'C')
	{
		sa_move(stack, 'c');
		sb_move(stack, 'c');
	}
	if (c == 'm')
		ft_printf("ss\n");
	stack->moves++;
}

void	pa_move(t_stack *stack, char c)
{
	int	i;
	int	j;

	if (stack->len_b == 0)
		return ;
	if (c == 'm' || c == 'C')
	{
		i = stack->len_a;
		j = i - 1;
		while (j >= 0)
			stack->a[i--] = stack->a[j--];
		stack->a[0] = stack->b[0];
		i = 0;
		j = 1;
		while (j < stack->len_b)
			stack->b[i++] = stack->b[j++];
		stack->len_a++;
		stack->len_b--;
	}
	if (c == 'm')
		ft_printf("pa\n");
	stack->moves++;
	find_middle(stack);
}

void	pb_move(t_stack *stack, char c)
{
	int	i;
	int	j;

	if (stack->len_a == 0)
		return ;
	if (c == 'm' || c == 'C')
	{
		i = stack->len_b;
		j = i - 1;
		while (j >= 0)
			stack->b[i--] = stack->b[j--];
		stack->b[0] = stack->a[0];
		i = 0;
		j = 1;
		while (j < stack->len_a)
			stack->a[i++] = stack->a[j++];
		stack->len_b++;
		stack->len_a--;
	}
	if (c == 'm')
		ft_printf("pb\n");
	stack->moves++;
	find_middle(stack);
}
