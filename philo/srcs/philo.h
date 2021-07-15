/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:55:28 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/15 19:12:58 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR -1

# define EAT 0
# define SLEEP 1
# define THINK 2
# define FORK 3
# define DIE 4

# define FREE_STATUS 1
# define FREE_SHARE 2
# define FREE_FORK 3
# define FREE_ALL 4

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
	int				own_num;
	t_config		*cfg;
	int				status;
	struct timeval	start_eat;
	pthread_mutex_t	status_mutex;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_share			*share;
	pthread_t		thread;
}			t_philo;

typedef struct s_status {
	t_config	cfg;
	t_share		share;
	t_fork		*fork;
	t_philo		*philo;
}			t_status;

int		arg_parse(t_status *status, int argc, char **argv);

int		print_status(int status, struct timeval *now_time, \
			pthread_mutex_t *mutex, int philo_num);

int		share_check_stop(t_share *share);
int		share_change_stop(t_share *share, int flag);

int		status_init(t_status **status);
int		status_set(t_status *status);
void	status_free(t_status *status, int flag);

int		share_init(t_share *share);
void	share_free(t_share *share);

int		fork_init(t_fork **forks, int num);
void	fork_free(t_fork *forks, int num);

int		philo_init(t_status *status);
void	philo_free(t_philo *philo, int num);
void	philo_thread(t_philo *philo);

int		ft_malloc(void *pointer, size_t type_size, size_t n);
int		ft_free(void *pointer);

size_t	ft_strlen(const char *c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_isdigit(int c);

void	debug_config(t_status *status);

#endif
