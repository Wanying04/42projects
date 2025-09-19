/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:09:01 by wtang             #+#    #+#             */
/*   Updated: 2025/09/19 15:18:09 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	mutex;

long long	get_timestamp(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "Error: gettimeofday() failed\n", 29);
		return (-1);
	}
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}

void	*routine()
{
	pthread_mutex_lock(&mutex);
	printf("timestamp_in_ms X has taken a fork");
	printf("timestamp_in_ms X is eating");
	printf("timestamp_in_ms X is sleeping");
	printf("timestamp_in_ms X is thinking");
	printf("timestamp_in_ms X died");
	pthread_mutex_unlock(&mutex);
}

void	*waiter()
{
	
}

int	main(int ac, char **av)
{
	int	i;
	int	j;
	pthread_t	p;

	if (ac < 5 || ac > 6)
		return (1);
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (ft_isdigit(av[i][j]) == 0)
				return (1);
			j++;
		}
		i++;
	}


	pthread_mutex_init(&mutex, NULL);
	pthread_create(&p, NULL, &routine, NULL);
	pthread_join(&p, NULL);
	pthread_mutex_destroy(&mutex);
}
