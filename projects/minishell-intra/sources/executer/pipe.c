/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:30:08 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

void	init_pipes(t_minir *mini)
{
	int	i;

	mini->pipesfd = ft_calloc(mini->nb_pipes + 1, sizeof(int *));
	if (!mini->pipesfd)
		return ;
	i = -1;
	while (++i < mini->nb_pipes)
	{
		mini->pipesfd[i] = malloc(2 * sizeof(int));
		pipe(mini->pipesfd[i]);
	}
}

int	count_pipes(t_minir *mini)
{
	int	i;

	mini->nb_pipes = 0;
	i = 0;
	while (mini->split_arr[i])
	{
		if (!ft_strcmp(mini->split_arr[i], "|"))
			mini->nb_pipes++;
		i++;
	}
	if (mini->nb_pipes == 0)
		return (0);
	return (1);
}

void	write_to_pipe(t_minir *mini)
{
	if (mini->pipe_index >= mini->nb_pipes)
		return ;
	close(mini->pipesfd[mini->pipe_index][0]);
	dup2(mini->pipesfd[mini->pipe_index][WRITE_END], STDOUT_FILENO);
	if (mini->pipesfd[mini->pipe_index] == NULL)
		close(mini->pipesfd[mini->pipe_index][1]);
}

void	read_from_pipe(t_minir *mini)
{
	close(mini->pipesfd[mini->pipe_index][1]);
	dup2(mini->pipesfd[mini->pipe_index][READ_END], STDIN_FILENO);
	if (mini->pipesfd[mini->pipe_index] == NULL)
		close(mini->pipesfd[mini->pipe_index][0]);
}

void	close_pipeline(t_minir *mini)
{
	if (mini->pipe_index > 0)
		close(mini->pipesfd[mini->pipe_index - 1][READ_END]);
	if (mini->pipe_index < mini->nb_pipes)
		close(mini->pipesfd[mini->pipe_index][WRITE_END]);
}
