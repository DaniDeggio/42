/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:30:31 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	redir(t_minir *mini)
{
	create_file(mini, mini->arr2[0], mini->redir);
	if (mini->i_redir == mini->y + 1)
		dup2(mini->red_fd, 1);
	close(mini->red_fd);
	return (0);
}

int	create_file(t_minir *mini, char *str, int redir)
{
	char	**name;

	name = ft_split(str, ' ');
	if (redir == 1)
		mini->red_fd = open(name[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		mini->red_fd = open(name[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (mini->red_fd < 0)
	{
		mini->exit_code = 1;
		ft_putstr_fd("cannot create the file", 2);
		return (free_arr(name));
	}
	mini->exit_code = 0;
	return (free_arr(name));
}
