/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:55:50 by dde-giov          #+#    #+#             */
/*   Updated: 2023/11/06 17:03:47 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "ft_printf/ft_printf.h"
# include "get_next_line/get_next_line.h"

typedef struct s_stack
{
	int	*a;
	int	*b;
	int	len_a;
	int	len_b;
	int	half_a;
	int	half_b;
	int	moves;
}				t_stack;

//sorting
int		sorting(t_stack *stack);
void	sort_three(t_stack *stack, int *stk);
void	sort_five(t_stack *stack, int *stk);
void	sort_hundred(t_stack *stack);

//sort_utils
void	optimize_push(t_stack *stack, int i, char c);
void	push_back(t_stack *stk);
int		find_min_max(int *stk, int len, char c);
int		find_pos(int *stk, int len, int n, char c);
void	find_middle(t_stack *stk);

//sorting_utils
int		moves_make_counta(t_stack *stk, int n, int i, char c);
void	other_case(t_stack *stk, int pos, int i, char c);
int		moves_make_countb(t_stack *stk, int n, int i, char c);
void	other_caseb(t_stack *stk, int pos, int i, char c);
void	frist_small(t_stack *stk);

//utils
void	ft_exit(int i, t_stack *stk);
int		check_stk(t_stack *stack, int *stk, int i, int len);
void	free_tmp(char **tmp);
void	check_max(t_stack *stk, char **tmp, int i);

//stack_maker
int		ft_check_tmp(char **tmp, int i);
int		ft_check_stack(t_stack *stack);
void	singleav(char **av, t_stack *stack);
void	multipleav(int ac, char **av, t_stack *stack);

//moves_ps
void	sa_move(t_stack *stack, char c);
void	sb_move(t_stack *stack, char c);
void	ss_move(t_stack *stack, char c);
void	pa_move(t_stack *stack, char c);
void	pb_move(t_stack *stack, char c);

//moves_r
void	ra_move(t_stack *stack, char c);
void	rb_move(t_stack *stack, char c);
void	rr_move(t_stack *stack, char c);

//moves_rr
void	rra_move(t_stack *stack, char c);
void	rrb_move(t_stack *stack, char c);
void	rrr_move(t_stack *stack, char c);

//libft_function
long	ft_atoi(const char *str);
int		ft_isdigit(int c);
int		ft_strcmp( const char *str1, const char *str2);

//ft_split
char	**ft_split(const char *str, char c);

#endif