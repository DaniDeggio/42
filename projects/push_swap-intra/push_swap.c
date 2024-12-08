/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 20:07:11 by dde-giov          #+#    #+#             */
/*   Updated: 2023/10/12 17:49:30 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_stack	*stack;

	if (ac == 1)
		return (0);
	stack = malloc(sizeof(t_stack));
	if (ac == 2)
		singleav(av, stack);
	else if (ac > 2)
		multipleav(ac, av, stack);
	stack->len_b = 0;
	ft_check_stack(stack);
	sorting(stack);
	ft_exit(9, stack);
	return (0);
}
