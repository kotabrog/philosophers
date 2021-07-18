/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 10:18:09 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/18 10:58:55 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
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
# define FREE_ALL 3

# define MAX_PHILO 100

# define SEM_NAME_FORK ("/semaphore_forks")
# define SEM_NAME_DATA ("/semaphore_data")

typedef struct s_config {
	int		num_philo;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		stop_eat_times;
}			t_config;

typedef struct s_share {
	int		stop_flag;
	int		stop_eat_count;
	sem_t	*sem;
	sem_t	*fork_sem;
}			t_share;

typedef struct s_philo {
	int				own_num;
	t_config		*cfg;
	struct timeval	start_eat;
	int				eat_count;
	int				before_time;
	t_share			*share;
	pthread_t		thread;
}			t_philo;

typedef struct s_status {
	t_config	cfg;
	t_share		share;
	t_philo		*philo;
	pthread_t	thread;
}			t_status;

int		arg_parse(t_status *status, int argc, char **argv);

int		status_init(t_status **status);
int		status_set(t_status *status);
void	status_free(t_status *status, int flag);

int		share_init(t_share *share, int fork_num);
void	share_free(t_share *share);

int		philo_init(t_status *status);

int		ft_malloc(void *pointer, size_t type_size, size_t n);
int		ft_free(void *pointer);

size_t	ft_strlen(const char *c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int		ft_isdigit(int c);

#endif
