/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 18:48:03 by wtang             #+#    #+#             */
/*   Updated: 2025/09/13 10:39:19 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\n' || *nptr == '\r'
		|| *nptr == '\v' || *nptr == '\f')
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		i = i * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * i);
}

void	send_char(int pid, char c)
{
	int	bit;
	
	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit--;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc != 3)
	{
		printf("Usage: %s <pid> <message>\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	i = 0;
	while (argv[2][i])
		send_char(pid, argv[2][i++]);
	send_char(pid, '\0');
	return (0);
}
