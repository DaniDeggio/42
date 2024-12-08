/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04a_error_messages.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:25:23 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:29:40 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

void	command_not_found(char *str, t_minir *mini)
{
	ft_putstr_fd("minihell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	if (mini->i_redir > mini->i_readfile)
		mini->y = mini->i_redir + 1;
	else if (mini->i_readfile != 0)
		mini->y = mini->i_readfile + 1;
}

int	read_file_error(t_minir *mini, char *file, int flag)
{
	if (!flag)
		ft_putstr_fd("minihell: ", 2);
	else
		ft_putstr_fd("minihell: cd: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	mini->exit_code = 1;
	mini->skip = 1;
	return (1);
}

int	exit__err(char *str, t_minir *mini)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	mini->exit_code = 2;
	return (mini->exit_code);
}
