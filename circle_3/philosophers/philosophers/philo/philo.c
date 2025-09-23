/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:09:01 by wtang             #+#    #+#             */
/*   Updated: 2025/09/23 18:58:12 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	*ft_routine(void *arg)
{
	long	current_time;
	t_philo *philo = (t_philo *)arg;

	if (philo = NULL)
		return (NULL);
	while (philo->data->all_ready == 0)
		usleep(100);
	philo->last_pasta_time = 0;
	while (1)
	{
		current_time = ft_get_time() - philo->data->start_time;
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(&philo->right_fork);
		printf("timestamp_in_ms %d has taken a fork", philo->p_id);
		printf("timestamp_in_ms %d is eating", philo->p_id);
		usleep(philo->time_to_eat * 1000);
		pthread_mutex_unlock(&philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);	
		printf("timestamp_in_ms %d is sleeping", philo->p_id);
		usleep(philo->time_to_sleep * 1000);
		printf("timestamp_in_ms %d is thinking", philo->p_id);
	}
}

int	main(int ac, char **av)
{
	t_philo	main_philo;
	t_data	data;

	if (ft_check_args(ac, av) == 0 || ft_init_philo(ac, av, &main_philo) == 0)
		return (1);
	if (!ft_init_simulation(&data, &main_philo))
		return (1);
	if (!ft_create_threads(&data))
		return (1);
	
	printf("timestamp_in_ms %d died", philo->p_id);
	
	pthread_mutex_destroy(&mutex);
	return (0);
}

long long	ft_get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		write(2, "Error: gettimeofday() failed\n", 29);
		return (0);
	}
	return (time.tv_sec * 1000LL + time.tv_usec / 1000);
}

int	ft_create_threads(t_data *data)
{
	int	i;

	data->start_time = 0;
	data->all_ready = 0;
	i = 0;
	while (i < data->philo_count)
	{
		if (pthread_create(&data->threads[i], NULL, &ft_routine, &data->philos[i]) != 0)
			return (0);
		i++;
	}
	usleep(1000);
	data->start_time = ft_get_time();
	data->all_ready = 1;
	return (1);
}

int	ft_init_simulation(t_data *data, t_philo *main_philo)
{
	int	i;

	data->philo_count = main_philo->number_of_philosophers;
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	data->threads = malloc(sizeof(pthread_t) * data->philo_count);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	if (!data->philos || !data->threads || !data->forks)
		return (0);
	i = 0;
	while (i < data->philo_count)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->philo_count)
	{
		data->philos[i] = *main_philo;
		data->philos[i].p_id = i + 1;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->philo_count];
		i++;
	}
	return (1);
}

int	ft_init_philo(int ac, char **av, t_philo *main_philo)
{
	memset(main_philo, 0, sizeof(t_philo));
	main_philo->number_of_philosophers = ft_atoi(av[1]);
	main_philo->time_to_die = ft_atoi(av[2]);
	main_philo->time_to_eat = ft_atoi(av[3]);
	main_philo->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		main_philo->max_pastas = ft_atoi(av[5]);
	else
		main_philo->max_pastas = -1;
	if (main_philo->time_to_die <= 0 || main_philo->time_to_eat <= 0 || main_philo->time_to_sleep <= 0)
		return (0);
	if (main_philo->number_of_philosophers < 1 || main_philo->number_of_philosophers > 200)
		return (0);
	if (main_philo->time_to_die < main_philo->time_to_eat || main_philo->time_to_die < main_philo->time_to_sleep)
		return (0);
	return (1);
}

int	ft_check_args(int ac, char *av[])
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
	return (1);
}