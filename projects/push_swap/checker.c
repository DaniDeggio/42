/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:55:07 by dde-giov          #+#    #+#             */
/*   Updated: 2023/10/12 19:55:09 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_moves(char *mv, t_stack *stk)
{
	if (ft_strcmp(mv, "sa\n") == 0)
		sa_move(stk, 'C');
	else if (ft_strcmp(mv, "sb\n") == 0)
		sb_move(stk, 'C');
	else if (ft_strcmp(mv, "ss\n") == 0)
		ss_move(stk, 'C');
	else if (ft_strcmp(mv, "pa\n") == 0)
		pa_move(stk, 'C');
	else if (ft_strcmp(mv, "pb\n") == 0)
		pb_move(stk, 'C');
	else if (ft_strcmp(mv, "ra\n") == 0)
		ra_move(stk, 'C');
	else if (ft_strcmp(mv, "rb\n") == 0)
		rb_move(stk, 'C');
	else if (ft_strcmp(mv, "rr\n") == 0)
		rr_move(stk, 'C');
	else if (ft_strcmp(mv, "rra\n") == 0)
		rra_move(stk, 'C');
	else if (ft_strcmp(mv, "rrb\n") == 0)
		rrb_move(stk, 'C');
	else if (ft_strcmp(mv, "rrr\n") == 0)
		rrr_move(stk, 'C');
	else
		ft_exit(2, stk);
	return (0);
}

int	main(int ac, char **av)
{
	t_stack	*stk;
	char	*mv;

	if (ac == 1)
		return (0);
	stk = malloc(sizeof(t_stack));
	if (ac == 2)
		singleav(av, stk);
	else if (ac > 2)
		multipleav(ac, av, stk);
	stk->len_b = 0;
	mv = get_next_line(0);
	while (mv)
	{
		check_moves(mv, stk);
		free(mv);
		mv = get_next_line(0);
	}
	ft_check_stack(stk);
	if (check_stk(stk, stk->a, 0, stk->len_a) == 0)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	ft_exit(9, stk);
	return (0);
}
