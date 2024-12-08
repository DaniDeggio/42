/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_word_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:30:47 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	copy_exit_code(t_minir *mini, int i)
{
	ft_itoa_custom(mini->exit_code, mini);
	i += 2;
	return (i);
}

int	copy_dble_dollar(int i, t_minir *mini)
{
	i += 2;
	mini->i_flag_dol += 2;
	mini->arr2[mini->y2][mini->x2++] = '$';
	mini->arr2[mini->y2][mini->x2++] = '$';
	return (i);
}

void	ft_count_exp_print_error(t_minir *mini)
{
	mini->mem_space = ft_intsize(mini->exit_code);
	mini->i += 2;
	mini->i_flag_dol++;
}

int	ft_strlen_name_var(char *s, int *i, int len_name_var)
{
	len_name_var = (*i);
	while (s[*i] != '"' && s[*i] != ' ' && s[*i] != '$' && s[*i])
		(*i)++;
	len_name_var = (*i) - len_name_var;
	return (len_name_var);
}
