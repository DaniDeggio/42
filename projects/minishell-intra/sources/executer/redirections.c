/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:30:34 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	do_red(t_minir *mini)
{
	int	y;

	if (mini->frirst_redir && mini->y == 0)
		mini->y--;
	y = mini->y;
	if (mini->read_from_pipe)
		read_from_pipe(mini);
	check_read_file(mini);
	mini->y = y;
	check_redir(mini);
	if (mini->i_redir > mini->i_readfile)
		mini->y = mini->i_redir + 1;
	else if (mini->i_readfile != 0)
		mini->y = mini->i_readfile + 1;
	if (mini->split_arr[mini->y] && mini->split_arr[mini->y + 1])
		next_step_sub(mini);
	if (mini->write_to_pipe && mini->read_from_pipe)
		mini->pipe_index++;
	if (mini->write_to_pipe)
		write_to_pipe(mini);
	mini->y = y;
	if (mini->flag3)
		get_arr3(mini);
	return (0);
}

int	check_redir(t_minir *mini)
{
	while (mini->i_redir > mini->y)
	{
		reset_flags2(mini);
		next_step_sub(mini);
		if (mini->redir)
		{
			free_arr(mini->arr2);
			get_arr2(mini->split_arr[mini->y + 2], mini, 1);
			mini->flag3 = 1;
			redir(mini);
		}
		mini->y += 2;
	}
	return (0);
}

int	check_read_file(t_minir *mini)
{
	while (mini->i_readfile > mini->y)
	{
		reset_flags2(mini);
		next_step_sub(mini);
		if (mini->heredoc)
		{
			free_arr(mini->arr2);
			get_arr2(mini->split_arr[mini->y + 2], mini, 1);
			mini->flag3 = 1;
			mini->exit_code = heredoc(mini);
		}
		if (mini->read_from_file)
		{
			free_arr(mini->arr2);
			get_arr2(mini->split_arr[mini->y + 2], mini, 1);
			mini->flag3 = 1;
			if (mini->y + 1 == mini->i_readfile)
				read_from_file(mini);
		}
		mini->y += 2;
	}
	return (0);
}

void	reset_flags2(t_minir *mini)
{
	mini->redir = 0;
	mini->read_from_file = 0;
	mini->heredoc = 0;
}

int	frist_redir(t_minir *mini)
{
	mini->y--;
	next_step_sub(mini);
	red_index(mini);
	mini->y++;
	mini->frirst_redir = 1;
	return (0);
}
