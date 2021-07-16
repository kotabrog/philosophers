/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:54:12 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/16 17:37:11 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_status_put(int status, suseconds_t time, int num)
{
	if (status == EAT)
		printf("%ld %d is eating\n", time, num);
	else if (status == SLEEP)
		printf("%ld %d is sleeping\n", time, num);
	else if (status == THINK)
		printf("%ld %d is thinking\n", time, num);
	else if (status == FORK)
		printf("%ld %d has taken a fork\n", time, num);
	else if (status == DIE)
		printf("%ld %d died\n", time, num);
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
		if (status1 == DIE)
			share->stop_flag = TRUE;
		print_status_put(status1, time.tv_usec / N_TO_M, philo->own_num);
		if (status2 != -1)
		{
			time_update(philo, &time);
			print_status_put(status2, time.tv_usec / N_TO_M, philo->own_num);
		}
	}
	if (pthread_mutex_unlock(&(share->mutex)))
		return (ERROR);
	return (flag);
}
