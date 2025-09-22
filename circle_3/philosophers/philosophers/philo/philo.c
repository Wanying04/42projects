/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:09:01 by wtang             #+#    #+#             */
/*   Updated: 2025/09/22 18:27:54 by wtang            ###   ########.fr       */
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

typedef struct s_philo
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_pastas;
} t_philo;

int	ft_check_args(int ac, char *av[], t_philo philo)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (0);
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (ft_isdigit(av[i][j]) == 0)
				return (0);
			j++;
		}
		i++;
	}
	if (philo.number_of_philosophers <= 0 || philo.time_to_die <= 0 || philo.time_to_eat <= 0 || philo.time_to_sleep <= 0)
		return (0);
	if (philo.number_of_philosophers < 1 || philo.number_of_philosophers > 200)
		return (0);
	if (philo.time_to_die < philo.time_to_eat || philo.time_to_die < philo.time_to_sleep)
		return (0);
	return (1);
}

int	ft_init_philo(int ac, char **av, t_philo philo)
{
	philo.number_of_philosophers = ft_atoi(av[1]);
	philo.time_to_die = ft_atoi(av[2]);
	philo.time_to_eat = ft_atoi(av[3]);
	philo.time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo.max_pastas = ft_atoi(av[5]);
	// 初始化互斥锁等资源
}

int	main(int ac, char **av)
{
	t_philo	philo;
	pthread_t	p;

	if (ft_check_args(ac, av) == 0)
		return (1);
	if (ft_init_philo(ac, av, philo) == 0)
		return (1);
		
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&p, NULL, &routine, NULL);
	pthread_join(p, NULL);
	pthread_mutex_destroy(&mutex);
	return (0);
}
