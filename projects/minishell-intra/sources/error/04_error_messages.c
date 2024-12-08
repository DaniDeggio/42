/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_error_messages.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:29:37 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	return_pipe_error(t_minir *mini)
{
	ft_putstr_fd("parse error near `|'\n", 2);
	mini->exit_code = 2;
	return (1);
}

int	return_lt_error(t_minir *mini)
{
	ft_putstr_fd("parse error near `<'\n", 2);
	mini->exit_code = 2;
	return (1);
}

int	return_gt_error(t_minir *mini)
{
	ft_putstr_fd("parse error near `>'\n", 2);
	mini->exit_code = 2;
	return (1);
}

int	return_nl_error(t_minir *mini)
{
	ft_putstr_fd("syntax error near unexpected token 'newline'\n", 2);
	mini->exit_code = 2;
	return (1);
}

int	return_not_required(t_minir *mini)
{
	ft_putstr_fd("command not required by subject\n", 2);
	mini->exit_code = 2;
	return (1);
}
