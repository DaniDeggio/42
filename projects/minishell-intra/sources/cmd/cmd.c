/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:24:40 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:27:58 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

void	line_to_cmd(char *s, t_minir *mini)
{
	add_history(s);
	init_splitarr(s, mini);
	mini->y = 0;
	if (count_pipes(mini))
		init_pipes(mini);
	while (mini->split_arr[mini->y] && !verify_readline(s, mini))
	{
		set_next_flag(mini);
		get_arr2(mini->split_arr[mini->y], mini, 0);
		mini->exit_code = do_builtin(mini);
		add_index_to_custom_env(mini);
		if (mini->local_var != NULL)
			add_index_to_local_var(mini);
		free_arr(mini->arr2);
		if (!mini->split_arr[mini->y + 1])
			break ;
		mini->y += 2;
	}
	free_arr(mini->split_arr);
	if (mini->nb_pipes != 0)
		ft_delete_matrix(mini->pipesfd);
	free(s);
}
