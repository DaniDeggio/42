/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:55:13 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

void	get_arr3(t_minir *mini)
{
	mini->y3 = 0;
	mini->arr3 = malloc((count_arr3(mini) + 1) * sizeof(char *));
	init_arr3(mini);
	free_arr(mini->arr2);
	if (mini->y == -1)
		get_arr2(mini->split_arr[mini->y + 1], mini, 1);
	else
		get_arr2(mini->split_arr[mini->y], mini, 1);
	if (mini->frirst_redir && mini->arr3[0] == NULL)
		mini->skip = 1;
	else
		mini->skip = 0;
	mini->frirst_redir = 0;
}

void	init_arr3(t_minir *mini)
{
	int	y;
	int	y2;

	y = mini->y;
	if (mini->frirst_redir && mini->y == -1)
		y += 2;
	while (y <= mini->i_redir + 1 || y <= mini->i_readfile + 1)
	{
		free_arr(mini->arr2);
		get_arr2(mini->split_arr[y], mini, 1);
		if (mini->y3 == 0 && !mini->frirst_redir)
			y2 = 0;
		else
			y2 = 1;
		while (mini->arr2[y2])
		{
			mini->arr3[mini->y3] = ft_strdup(mini->arr2[y2]);
			mini->y3++;
			y2++;
		}
		y += 2;
	}
	mini->arr3[mini->y3] = NULL;
}

int	count_arr3(t_minir *mini)
{
	int	y;
	int	count;

	y = mini->y;
	if (mini->frirst_redir)
		y += 2;
	count = 0;
	while (y <= mini->i_redir + 1 || y <= mini->i_readfile + 1)
	{
		ft_count_words(mini->split_arr[y], mini);
		count += mini->count_words - 1;
		y += 2;
	}
	return (count);
}
