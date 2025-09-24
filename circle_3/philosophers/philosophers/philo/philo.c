/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:09:01 by wtang             #+#    #+#             */
/*   Updated: 2025/09/24 17:14:42 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	must_stop(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->finish_mutex);
	stop = data->stop_simulation;
	pthread_mutex_unlock(&data->finish_mutex);
	return (stop);
}

void	mark_philo_finished(t_data *data, int id)
{
	long long	current_time;
	
	pthread_mutex_lock(&data->finish_mutex);
	if (data->pastas_count[id - 1] == 0)
	{
		data->pastas_count[id - 1] = 1;
		data->finished_count++;
		if (data->finished_count >= data->philo_count)
			data->stop_simulation = 1;
	}
	pthread_mutex_unlock(&data->finish_mutex);
	current_time = ft_get_time() - data->start_time;
	printf("%lld They all ate %d times\n", current_time, data->philos->pastas_eaten);
}

void	*death_checker(void *arg)
{
	t_data *data = (t_data *)arg;
	int	i;
	long long	current_time;
	
	i = 0;
	while (1)
	{
		if (must_stop(data))
			break;
		while (i < data->philo_count)
		{
			if (ft_get_time() - data->philos[i].last_pasta_time > data->philos->time_to_die)
			{
				pthread_mutex_lock(&data->finish_mutex);
				data->stop_simulation = 1;
				pthread_mutex_unlock(&data->finish_mutex);
				current_time = ft_get_time() - data->start_time;
				printf("%lld %d died\n", current_time, data->philos->p_id);
				break;
			}
		}
		usleep(1000);
	}
	return (NULL);
}

void	*ft_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	long long	current_time;
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo == NULL)
		return (NULL);
	while (philo->data->all_ready == 0)
		usleep(100);
	philo->last_pasta_time = ft_get_time();
	philo->pastas_eaten = 0;
	while (1)
	{
		if (must_stop(philo->data))
			break;
		if ((philo->p_id - 1) < (philo->p_id) % philo->data->philo_count)
		{
			first_fork = philo->left_fork;
			second_fork = philo->right_fork;
		}
		else
		{
			first_fork = philo->right_fork;
			second_fork = philo->left_fork;
		}
		pthread_mutex_lock(first_fork);
		current_time = ft_get_time() - philo->data->start_time;
		printf("%lld %d has taken a fork\n", current_time, philo->p_id);
		pthread_mutex_lock(second_fork);
		current_time = ft_get_time() - philo->data->start_time;
		printf("%lld %d has taken a fork\n", current_time, philo->p_id);
		philo->last_pasta_time = ft_get_time();
		current_time = ft_get_time() - philo->data->start_time;
		printf("%lld %d is eating\n", current_time, philo->p_id);
		usleep(philo->time_to_eat * 1000);
		philo->pastas_eaten++;
		pthread_mutex_unlock(second_fork);
		pthread_mutex_unlock(first_fork);
		if (philo->max_pastas > 0 && philo->pastas_eaten >= philo->max_pastas)
			mark_philo_finished(philo->data, philo->p_id);
		if (must_stop(philo->data))
			break;
		current_time = ft_get_time() - philo->data->start_time;
		printf("%lld %d is sleeping\n", current_time, philo->p_id);
		usleep(philo->time_to_sleep * 1000);
		current_time = ft_get_time() - philo->data->start_time;
		printf("%lld %d is thinking\n", current_time, philo->p_id);
	}
	return (NULL);
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
		

	
	pthread_mutex_destroy();
	return (0);
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

	
	data->finished_count = 0;
	data->stop_simulation = 0;
	data->philo_count = main_philo->number_of_philosophers;
	data->philos = malloc(sizeof(t_philo) * data->philo_count);
	data->threads = malloc(sizeof(pthread_t) * data->philo_count);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_count);
	data->pastas_count = malloc(sizeof(int) * data->philo_count);
	memset(data->pastas_count, 0, sizeof(int) * data->philo_count);
	if (!data->philos || !data->threads || !data->forks || !data->pastas_count)
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
	pthread_mutex_init(&data->finish_mutex, NULL);
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