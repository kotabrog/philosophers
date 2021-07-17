/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:54:12 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/17 13:08:47 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status_put(int status, suseconds_t time, int num)
{
	int	int_time;

	int_time = (int)(time / N_TO_M);
	if (status == EAT)
		printf("%d %d is eating\n", int_time, num);
	else if (status == SLEEP)
		printf("%d %d is sleeping\n", int_time, num);
	else if (status == THINK)
		printf("%d %d is thinking\n", int_time, num);
	else if (status == FORK)
		printf("%d %d has taken a fork\n", int_time, num);
	else if (status == DIE)
		printf("%d %d died\n", int_time, num);
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
