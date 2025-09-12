/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:48:03 by wtang             #+#    #+#             */
/*   Updated: 2025/09/12 20:16:33 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

volatile sig_atomic_t		g_ack_received = 0;

void	ack_handler(int sig)
{
	if (sig == SIGUSR1)
		g_ack_received = 1;
	else if (sig == SIGUSR2)
	{
		printf("Message delivered successfully!\n");
		exit(EXIT_SUCCESS);
	}
}

void	send_char(pid_t server_pid, char c)
{
	int	bit;
	
	bit = 7;
	while (bit >= 0)
	{
		g_ack_received = 0;
		
		if ((c >> bit) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(500);
		if (!g_ack_received)
		{
			printf("Error: No acknowledgement from server\n");
			exit(EXIT_FAILURE);
		}
		bit--;
	}
}

void	send_message(pid_t server_pid, const char *message)
{
	int	i;

	struct sigaction	sa;
	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (message[i])
	{
		send_char(server_pid, message[i]);
		i++;
	}
	send_char(server_pid, '\0');
	printf("Waiting for final acknowledgement...\n");
	sleep(3);
	printf("Error: Final acknowledgement timeout\n");
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	__pid_t	server_pid;

	if (argc != 3)
	{
		printf("Usage: %s <server_pid> <message>\n", argv[0]);
		printf("Example: %s 1234 \"Hello World\"\n", argv[0]);
		return (EXIT_FAILURE);
	}
	server_pid = atoi(argv[1]);
	if (server_pid <= 0)
	{
		printf("Error: Invalid server PID\n");
		return (EXIT_FAILURE);
	}
	printf("Client PID: %d\n", getpid());
	printf("Sending to server PID: %d\n", server_pid);
	printf("Message: %s\n", argv[2]);
	send_message(server_pid, argv[2]);
	return (EXIT_SUCCESS);
}
