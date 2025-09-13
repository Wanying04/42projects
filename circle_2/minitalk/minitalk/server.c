/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:48:18 by wtang             #+#    #+#             */
/*   Updated: 2025/09/13 10:39:31 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

static int	bit = 0;
static char	c = 0;

void	handler(int sig)
{
	if (sig == SIGUSR1)
		c |= (1 << (7 - bit));
	bit++;
	if (bit == 8)
	{
		if (c == 0)
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	printf("Server PID: %d\n", getpid());
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	while (1)
		pause();
	return (0);
}
