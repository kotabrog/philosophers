/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:55:28 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/13 20:14:37 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR -1

# define EAT 0
# define THINK 1
# define SLEEP 2

typedef struct s_fork {
	int				use_flag;
	pthread_mutex_t	mutex;
}			t_fork;

typedef struct s_config {
	int		num_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		stop_eat_times;
}			t_config;

typedef struct s_share {
	int				stop_flag;
	pthread_mutex_t	stop_mutex;
	int				stop_eat_count;
	pthread_mutex_t	eat_count_mutex;
	pthread_mutex_t	print_mutex;
}			t_share;

typedef struct s_philo {
	t_config		*cfg;
	int				status;
	struct timeval	start_eat;
	pthread_mutex_t	status_mutex;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_share			*share;
}			t_philo;

typedef struct s_status {
	t_config	cfg;
	t_share		share;
	t_philo		*philo;
	t_fork		*fork;
}			t_status;

int		ft_malloc(void *pointer, size_t type_size, size_t n);
int		ft_free(void *pointer);

#endif
