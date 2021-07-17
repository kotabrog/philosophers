/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:54:12 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/17 16:43:07 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status_put(int status, suseconds_t time, int num)
{
	int	int_time;

	int_time = (int)(time / N_TO_M);
	ft_putnbr_fd(int_time, 1);
	write(1, " ", 1);
	ft_putnbr_fd(num, 1);
	if (status == EAT)
		ft_putendl_fd(" is eating", 1);
	else if (status == SLEEP)
		ft_putendl_fd(" is sleeping", 1);
	else if (status == THINK)
		ft_putendl_fd(" is thinking", 1);
	else if (status == FORK)
		ft_putendl_fd(" has taken a fork", 1);
	else if (status == DIE)
		ft_putendl_fd(" died", 1);
}

int	print_status(int status1, int status2, t_philo *philo, t_share *share)
{
	struct timeval	time;
	int				flag;

	flag = SUCCESS;
	if (pthread_mutex_lock(&(share->mutex)))
		return (ERROR);
	if (gettimeofday(&time, NULL))
		flag = ERROR;
	if (!flag && !share->stop_flag)
	{
		flag = check_philo_die(philo, &time);
		if (!flag)
			print_status_put(status1, time.tv_usec, philo->own_num);
		if (!flag && status2 != -1)
		{
			time_update(philo, &time);
			print_status_put(status2, time.tv_usec, philo->own_num);
			eat_count(philo, share);
		}
	}
	if (pthread_mutex_unlock(&(share->mutex)))
		return (ERROR);
	return (-(flag < 0));
}
