/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:25:07 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:30:37 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	g_signal;

void	init(t_minir *mini, char **envp)
{
	rl_clear_history();
	set_signal();
	init_param(mini);
	mini->env_list = copy_env_in_list(envp);
	add_index_to_env_list(mini);
	mini->local_var = NULL;
}

void	init_param(t_minir *mini)
{
	g_signal = 0;
	mini->exit_code = 0;
	mini->index_list = 0;
	mini->i_flag_dol = 0;
	mini->flag_list = 0;
	mini->y = 0;
	mini->x = 0;
	mini->y2 = 0;
	mini->x2 = 0;
	mini->nb_tokens = 0;
	mini->pipe_index = 0;
}

void	reinit_param(t_minir *mini, char **envp)
{
	(void)envp;
	mini->nb_tokens = 0;
	mini->split_arr = NULL;
	mini->arr2 = NULL;
	mini->y = 0;
	mini->x = 0;
	mini->y2 = 0;
	mini->x2 = 0;
	mini->check_exp = NULL;
	mini->y_mx_envp = 0;
	mini->xenvp = 0;
	mini->pipe_index = 0;
	mini->i_readfile = 0;
	mini->i_redir = 0;
	mini->flag3 = 0;
}
