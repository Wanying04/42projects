/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:21:25 by wtang             #+#    #+#             */
/*   Updated: 2025/09/24 16:23:42 by wtang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data t_data;

typedef struct s_philo
{
	int	p_id;
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_pastas;
	int	pastas_eaten;
	long long	last_pasta_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data	*data;
} t_philo;

typedef struct s_data
{
	t_philo	*philos;
	pthread_mutex_t	*forks;
	pthread_t	*threads;
	int	philo_count;
	long long	start_time;
	int	all_ready;
	int	*pastas_count;
	int	finished_count;
	pthread_mutex_t	finish_mutex;
	int	stop_simulation;
} t_data;

#endif