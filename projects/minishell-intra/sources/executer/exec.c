/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:24:57 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:29:59 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	find_paths(t_minir *mini)
{
	t_listc	*tmp_list;

	tmp_list = mini->env_list;
	while (tmp_list)
	{
		if (ft_strncmp(tmp_list->cont, "PATH=", 5) == 0)
		{
			mini->paths = ft_split(tmp_list->cont + 5, ':');
			return (1);
		}
		tmp_list = tmp_list->next;
	}
	mini->paths = malloc(sizeof(char *) * 1);
	mini->paths[0] = 0;
	return (0);
}

int	do_execve(t_minir *mini)
{
	envp_to_matrix(mini);
	if (ft_strchr(mini->arr2[0], '.') || ft_strchr(mini->arr2[0], '/'))
	{
		if (!mini->flag3)
			mini->exit_code = ft_ecxev(mini->arr2[0], mini->arr2, mini->env);
		else
			mini->exit_code = ft_ecxev(mini->arr3[0], mini->arr3, mini->env);
	}
	else
	{
		if (!mini->flag3)
			mini->exit_code = bin_exec(mini, mini->arr2);
		else
			mini->exit_code = bin_exec(mini, mini->arr3);
	}
	free_arr(mini->env);
	return (mini->exit_code);
}

void	handle_parent_process(t_minir *mini)
{
	set_signal_avoid();
	waitpid(mini->pid, &mini->exit_code, 0);
	mini->exit_code = WEXITSTATUS(mini->exit_code);
	set_signal();
	if (g_signal == SIGINT)
	{
		printf("\n");
		mini->exit_code = 130;
	}
	g_signal = 0;
	if (mini->exit_code == 127)
		command_not_found(mini->arr2[0], mini);
	if (mini->read_from_pipe)
		mini->pipe_index++;
	close_pipeline(mini);
	free_arr(mini->paths);
}

int	exec(t_minir *mini)
{
	mini->pid = fork();
	find_paths(mini);
	if (mini->pid == -1)
	{
		ft_putstr_fd("fork failed", 2);
		return (1);
	}
	if (mini->pid == 0)
	{
		set_signal_child();
		if (!mini->skip)
			do_red(mini);
		if (!mini->skip)
			mini->exit_code = do_child_cmd(mini);
		exit(mini->exit_code);
	}
	handle_parent_process(mini);
	return (mini->exit_code);
}
