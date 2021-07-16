/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:55:28 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/16 22:12:41 by ksuzuki          ###   ########.fr       */
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

# define N_TO_M 1000

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
	int				stop_eat_count;
	pthread_mutex_t	mutex;
}			t_share;

typedef struct s_philo {
	int				own_num;
	t_config		*cfg;
	int				status;
	struct timeval	start_eat;
	int				eat_count;
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
	pthread_t	thread;
}			t_status;

int		arg_parse(t_status *status, int argc, char **argv);

int		eat(t_philo *philo);
void	eat_count(t_philo *philo, t_share *share);

int		print_status(int status1, int status2, t_philo *philo, t_share *share);

void	time_update(t_philo *philo, struct timeval *time);
int		set_start_time(t_philo *philo, int num);

void	check_die_thread(t_status *status);
int		share_check_stop(t_share *share);
int		share_change_stop(t_share *share, int flag);

int		share_init(t_share *share);
void	share_free(t_share *share);

int		fork_init(t_fork **forks, int num);
void	fork_free(t_fork *forks, int num);
int		fork_take(t_fork *one_fork, t_philo *philo, int eat_flag);
int		fork_release(t_fork *one_fork);

int		status_init(t_status **status);
int		status_set(t_status *status);
void	status_free(t_status *status, int flag);

int		philo_init(t_status *status);
void	philo_thread(t_philo *philo);

int		ft_malloc(void *pointer, size_t type_size, size_t n);
int		ft_free(void *pointer);

size_t	ft_strlen(const char *c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_isdigit(int c);

void	debug_config(t_status *status);

#endif
