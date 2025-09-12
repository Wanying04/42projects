/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:48:18 by wtang             #+#    #+#             */
/*   Updated: 2025/09/12 19:55:30 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handle_signal(int sig, siginfo_t *info, void *context)
{
	static int	bit_count = 0;
	static char	current_char = 0;
	static pid_t	client_pid = 0;
	(void)context;

	if (client_pid == 0)
		client_pid = info->si_pid;
	if (sig == SIGUSR1)
		current_char = (current_char << 1) | 1;
	else if (sig == SIGUSR2)
		current_char = (current_char << 1) | 0;
	bit_count++;
	if (bit_count == 8)
	{
		if (current_char == '\0')
		{
			write(1, "\n", 1);
			kill(client_pid, SIGUSR2);
			client_pid = 0;
		}
		else
		{
			write(1, &current_char, 1);
			kill(client_pid, SIGUSR1);
		}
		bit_count = 0;
		current_char = 0;
	}
	else
		kill(client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	printf("Server PID: %d\n", getpid());
	printf("Waiting for messages...\n");
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	return (0);
}
