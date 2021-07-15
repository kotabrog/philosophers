/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:54:12 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/15 18:31:07 by ksuzuki          ###   ########.fr       */
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

int	print_status(int status, struct timeval *now_time, \
	pthread_mutex_t *mutex, int philo_num)
{
	struct timeval	time;

	if (now_time == NULL)
	{
		if (gettimeofday(&time, NULL))
			return (ERROR);
	}
	else
		time.tv_usec = now_time->tv_usec;
	if (pthread_mutex_lock(mutex))
		return (ERROR);
	print_status_put(status, time.tv_usec, philo_num);
	if (pthread_mutex_unlock(mutex))
		return (ERROR);
	return (SUCCESS);
}
