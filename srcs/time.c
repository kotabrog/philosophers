/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 11:34:57 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/17 20:03:36 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	accurate_usleep(int limit_time, int start_time)
{
	struct timeval	time;
	int				elapsed_time;

	while (TRUE)
	{
		if (gettimeofday(&time, NULL))
			return (ERROR);
		elapsed_time = time.tv_usec - start_time;
		if (elapsed_time < 0)
			elapsed_time += 1000000;
		if ((elapsed_time / N_TO_M) >= limit_time)
			break ;
		usleep((limit_time * N_TO_M - elapsed_time) / 2);
	}
	return (SUCCESS);
}

int	check_elapsed_time(int start_time, int end_time, int limit_time)
{
	int	value;

	value = end_time - start_time;
	if (value < 0)
		value += 1000000;
	return ((value / N_TO_M) >= limit_time);
}

void	time_update(t_philo *philo, struct timeval *time, int is_eat)
{
	philo->before_time = time->tv_usec;
	if (is_eat)
	{
		philo->start_eat.tv_sec = time->tv_sec;
		philo->start_eat.tv_usec = time->tv_usec;
	}
}

int	set_start_time(t_philo *philo, int num)
{
	int	i;

	if (gettimeofday(&(philo[0].start_eat), NULL))
		return (ERROR);
	philo[0].before_time = philo[0].start_eat.tv_usec;
	i = 1;
	while (i < num)
	{
		philo[i].start_eat.tv_sec = philo[0].start_eat.tv_sec;
		philo[i].start_eat.tv_usec = philo[0].start_eat.tv_usec;
		philo[i].before_time = philo[0].start_eat.tv_usec;
		++i;
	}
	return (SUCCESS);
}
