/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:17:05 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:30:02 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

void	exit_free(t_minir *mini)
{
	free_arr(mini->arr2);
	free_arr(mini->split_arr);
	free_list(mini->local_var);
	free_list(mini->env_list);
	if (mini->nb_pipes != 0)
		ft_delete_matrix(mini->pipesfd);
}

void	ft_exit_custom(t_minir *mini)
{
	mini->exit_code = 0;
	if (mini->count_words == 1)
		mini->exit_code = 0;
	else if (mini->count_words == 2)
		mini->exit_code = ft_exit_02(mini);
	else
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		mini->exit_code = 1;
		return ;
	}
	exit_free(mini);
	write(1, "exit\n", 5);
	exit(mini->exit_code);
}

int	ft_exit_02(t_minir *mini)
{
	int		i;
	char	*str;
	int		flag;

	i = 0;
	str = mini->arr2[1];
	flag = -1;
	if (str[0] == '+' || str[0] == '-' || str [0] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			flag = 0;
			break ;
		}
		i++;
	}
	if (flag == 0)
		mini->exit_code = ft_atoi(str);
	else
		exit__err(str, mini);
	return (mini->exit_code);
}
