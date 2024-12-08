/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:28:16 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

void	heredoc_handler(int signum)
{
	if (signum == SIGQUIT)
	{
		unlink(".heredoc");
		exit(0);
	}
	else if (signum == SIGINT)
	{
		unlink(".heredoc");
		exit(130);
	}
}

void	signal_heredoc_handler(void)
{
	struct sigaction	sig;

	sig.sa_handler = heredoc_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig, NULL);
	sig.sa_handler = heredoc_handler;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGQUIT, &sig, NULL);
}

int	check_s_signal(char *s, t_minir *mini)
{
	int	check_s;

	check_s = 0;
	if (s == NULL)
	{
		check_s = 1;
		rl_clear_history();
		return (check_s);
	}
	if (g_signal == SIGINT)
	{
		mini->exit_code = 130;
	}
	g_signal = 0;
	return (check_s);
}
