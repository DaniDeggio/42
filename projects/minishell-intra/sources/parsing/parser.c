/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:25:15 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:30:39 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

void	red_index(t_minir *mini)
{
	int	y;

	y = mini->y + 1;
	while (mini->split_arr[y])
	{
		if (!ft_strcmp(mini->split_arr[y], ">")
			|| !ft_strcmp(mini->split_arr[y], ">>"))
			mini->i_redir = y;
		else if (!ft_strcmp(mini->split_arr[y], "<")
			|| !ft_strcmp(mini->split_arr[y], "<<"))
			mini->i_readfile = y;
		if (!ft_strcmp(mini->split_arr[y], "|"))
			break ;
		y += 2;
	}
}

void	reset_flags(t_minir *mini)
{
	mini->write_to_pipe = 0;
	mini->redir = 0;
	mini->read_from_pipe = 0;
	mini->read_from_file = 0;
	mini->heredoc = 0;
	mini->skip = 0;
	mini->frirst_redir = 0;
}

void	next_step_sub(t_minir *mini)
{
	if (!ft_strcmp(mini->split_arr[mini->y + 1], "|"))
		mini->write_to_pipe = 1;
	else if (!ft_strcmp(mini->split_arr[mini->y + 1], ">"))
		mini->redir = 1;
	else if (!ft_strcmp(mini->split_arr[mini->y + 1], ">>"))
		mini->redir = 2;
	else if (!ft_strcmp(mini->split_arr[mini->y + 1], "<"))
		mini->read_from_file = 1;
	else if (!ft_strcmp(mini->split_arr[mini->y + 1], "<<"))
		mini->heredoc = 1;
}

void	next_step_sub2(t_minir *mini)
{
	if (!ft_strcmp(mini->split_arr[mini->y - 1], "|"))
		mini->read_from_pipe = 1;
	if (!ft_strcmp(mini->split_arr[mini->y - 1], ">>")
		|| !ft_strcmp(mini->split_arr[mini->y - 1], ">"))
		mini->skip = 1;
	if (!ft_strcmp(mini->split_arr[mini->y - 1], "<"))
		mini->skip = 1;
	if (!ft_strcmp(mini->split_arr[mini->y - 1], "<<"))
		mini->skip = 1;
}

int	set_next_flag(t_minir *mini)
{
	reset_flags(mini);
	if ((mini->y == 0 || mini->y == 2) && (!ft_strcmp(mini->split_arr[0], ">")
			|| !ft_strcmp(mini->split_arr[0], ">>")
			|| !ft_strcmp(mini->split_arr[0], "<")
			|| !ft_strcmp(mini->split_arr[0], "<<")))
	{
		if (mini->y == 0)
			frist_redir(mini);
		else if (mini->y == 2)
		{
			mini->y--;
			next_step_sub2(mini);
		}
	}
	else
	{
		if (mini->split_arr[mini->y] && mini->split_arr[mini->y + 1])
			next_step_sub(mini);
		if (mini->y > 1)
			next_step_sub2(mini);
		red_index(mini);
	}
	return (0);
}
