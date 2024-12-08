/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:30:09 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:27:48 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minihell.h"

int	main(int ac, char **av, char **envp)
{
	char		*s;
	t_minir		mini;

	(void)ac;
	(void)av;
	init(&mini, envp);
	while (1)
	{
		s = prompt();
		if (check_s_signal(s, &mini))
			exit(0);
		reinit_param(&mini, envp);
		if (s && ft_isspace(s))
			line_to_cmd(s, &mini);
	}
}
