/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-giov <dde-giov@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:34:23 by dde-giov          #+#    #+#             */
/*   Updated: 2023/05/23 00:50:56 by dde-giov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int sig, siginfo_t *info, void *context)
{
	static int	bit;
	static int	character;

	(void)context;
	if (sig == SIGUSR1)
		character += 1 << bit;
	bit++;
	if (bit == 8)
	{
		ft_putchar_fd(character, 1);
		if (character == '\0')
			kill(info->si_pid, SIGUSR1);
		bit = 0;
		character = 0;
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	struct sigaction	act;

	if (argc != 1)
	{
		ft_printf("Error\nToo many arguments\n");
		exit(0);
	}
	pid = getpid();
	ft_printf("Pid: %u\n", pid);
	act.sa_sigaction = handler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	sigemptyset(&act.sa_mask);
	while (1)
		pause();
	return (0);
}
