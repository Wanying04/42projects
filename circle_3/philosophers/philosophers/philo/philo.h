/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtang <wtang@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:21:25 by wtang             #+#    #+#             */
/*   Updated: 2025/09/25 17:01:47 by wtang            ###   ########.fr       */
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
	pthread_mutex_t	pasta_mutex;
	int	finish_mutex_initialized;
	int	pasta_mutex_initialized;
} t_data;

long long	ft_get_time(void);
int	must_stop(t_data *data);
void	mark_philo_finished(t_data *data, int id);
void	*death_checker(void *arg);
void	print_status(t_philo *philo, const char *status);
void	*ft_routine(void *arg);
void	ft_clean_up(t_data *data);
int	ft_create_threads(t_data *data);
int	ft_init_simulation(t_data *data, t_philo *main_philo);
int	ft_init_philo(int ac, char **av, t_philo *main_philo);
int	ft_check_args(int ac, char *av[]);
int	ft_isdigit(int c);
int	ft_atoi(const char *nptr);

#endif