/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 23:34:06 by dde-giov          #+#    #+#             */
/*   Updated: 2024/02/20 13:30:27 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minihell.h"

int	read_from_file(t_minir *mini)
{
	if (red_input(mini, mini->arr2[0]))
		read_file_error(mini, mini->arr2[0], 0);
	return (0);
}

int	red_input(t_minir *mini, char *path)
{
	mini->red_fd = open(path, O_RDONLY);
	if (mini->red_fd < 0)
		return (1);
	dup2(mini->red_fd, 0);
	close(mini->red_fd);
	mini->exit_code = 0;
	return (0);
}

int	heredoc(t_minir *mini)
{
	if (heredoc_read(mini, mini->arr2[0]))
		return (1);
	close(mini->red_fd);
	if (mini->i_readfile != mini->y + 1)
		return (0);
	mini->red_fd = open(".heredoc", O_RDONLY);
	dup2(mini->red_fd, 0);
	if (red_input(mini, ".heredoc") || mini->red_fd < 0)
	{
		ft_putstr_fd("heredoc error\n", 2);
		unlink(".heredoc");
		return (1);
	}
	close(mini->red_fd);
	unlink(".heredoc");
	return (0);
}

int	heredoc_read(t_minir *mini, char *eof)
{
	char	*input;

	signal_heredoc_handler();
	mini->red_fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (mini->red_fd < 0)
	{
		ft_putstr_fd("heredoc error\n", 2);
		return (1);
	}
	while (1)
	{
		input = readline("> ");
		if (input == NULL || !ft_strcmp(input, eof))
		{
			if (input)
				free(input);
			else
				printf("Heredoc delimited by EndOfFile (wanted `%s')\n", eof);
			break ;
		}
		write(mini->red_fd, input, ft_strlen(input));
		write(mini->red_fd, "\n", 1);
		free(input);
	}
	return (0);
}
