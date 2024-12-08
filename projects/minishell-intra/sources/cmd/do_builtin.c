/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 01:05:53 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:30:05 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	check_builtin(t_minir *mini)
{
	if ((!ft_strncmp(mini->arr2[0], "export\0", 7) && mini->arr2[1])
		|| !ft_strncmp(mini->arr2[0], "unset\0", 6)
		|| !ft_strncmp(mini->arr2[0], "exit\0", 5)
		|| !ft_strncmp(mini->arr2[0], "cd\0", 3)
		|| ft_strchr(mini->arr2[0], '='))
		return (1);
	return (0);
}

int	do_builtin(t_minir *mini)
{
	if (!mini->write_to_pipe && ! mini->read_from_pipe
		&& !mini->read_from_file && !mini->redir && !mini->heredoc
		&& !mini->skip)
	{
		if (ft_strncmp(mini->arr2[0], "export\0", 7) == 0)
			return (ft_export(mini->arr2, mini));
		else if (ft_strncmp(mini->arr2[0], "unset\0", 6) == 0)
			return (ft_unset(mini->arr2, mini));
		else if (ft_strncmp(mini->arr2[0], "exit\0", 5) == 0)
		{
			ft_exit_custom(mini);
			return (0);
		}
		else if (ft_strncmp(mini->arr2[0], "cd\0", 3) == 0)
			return (ft_cd(mini->arr2, mini));
		else if (ft_strchr(mini->arr2[0], '=') != NULL
			&& ((mini->arr2[0][0] >= 65 && mini->arr2[0][0] <= 90)
			|| (mini->arr2[0][0] >= 97 && mini->arr2[0][0] <= 122))
			&& (mini->arr2[0][0] != '='))
			return (add_var(mini->arr2[0], mini));
	}
	mini->exit_code = exec(mini);
	return (mini->exit_code);
}

int	do_child_cmd(t_minir *mini)
{
	if (check_builtin(mini))
		return (0);
	if (ft_strncmp(mini->arr2[0], "pwd\0", 4) == 0)
		return (ft_pwd());
	else if (ft_strncmp(mini->arr2[0], "env\0", 4) == 0)
		return (ft_env(mini));
	else if (ft_strncmp(mini->arr2[0], "export\0", 7) == 0)
		return (ft_export(mini->arr2, mini));
	else if (ft_strncmp(mini->arr2[0], "echo\0", 5) == 0 && !mini->flag3)
		return (ft_echo(mini->arr2));
	else if (ft_strncmp(mini->arr2[0], "echo\0", 5) == 0 && mini->flag3)
		return (ft_echo(mini->arr3));
	else
		return (do_execve(mini));
}
