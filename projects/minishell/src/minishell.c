/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: deggio <deggio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:11:02 by deggio            #+#    #+#             */
/*   Updated: 2023/12/12 18:12:57 by deggio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parsec(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i] != NULL)
	{
		
		i++;
	}
}

int main(void)
{
	t_data *data;
	char *line;
	int n;

	data = (t_data *)malloc(sizeof(t_data));
	data->check = 1;
	while (data->check)
	{
		line = readline("minishell$> ");
		add_history(line);
		printf(" PORCO DIO: %s\n", line);
		if (line[0] == '\0')
		 	break;
		data->input = ft_split(line, '|');
		n = 0;
		while (data->input[n] != NULL)
		{
		 	printf("data->input[%d]: %s\n", n, data->input[n]);
		 	n++;
		}
		parsec(data);
		free(data->input);
		free(line);
	}
	return (0);
}
