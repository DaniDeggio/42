/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_verify_readline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:24:50 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:29:47 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	verify_readline(char *s, t_minir *mini)
{
	if (mini->y > mini->nb_tokens)
		return (1);
	if (error_end(s, '>', mini) || error_end(s, '<', mini)
		|| error_end(s, '|', mini))
		return (return_negative(mini));
	else if (error_begin_02(s, mini))
		return (return_negative(mini));
	else if (count_quotes(s))
		return (return_negative(mini));
	else if (error_begin(s, mini))
		return (return_negative(mini));
	else if (error_mixed_start(s, mini))
		return (return_negative(mini));
	else if (error_dollar(s, mini))
		return (return_negative(mini));
	return (0);
}

int	return_negative(t_minir *mini)
{
	mini->exit_code = 2;
	return (1);
}
