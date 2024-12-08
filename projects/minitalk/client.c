/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:34:33 by dde-giov          #+#    #+#             */
/*   Updated: 2023/05/23 03:06:09 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(int pid, char c)
{
	int		bit;

	bit = 0;
	while (bit < 8)
	{
		if ((c & (1 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit++;
		usleep(500);
	}
}

void	sended(int sig)
{
	ft_printf("The message has been sent\n");
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_printf("Error\nInsert PID and message\n");
		exit(0);
	}
	pid = ft_atoi(argv[1]);
	while (*argv[2])
		send_char(pid, *argv[2]++);
	signal(SIGUSR1, &sended);
	send_char(pid, '\n');
	send_char(pid, '\0');
	return (0);
}
