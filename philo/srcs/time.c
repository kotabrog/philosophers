/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 11:34:57 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/16 17:25:50 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	time_passed_check(struct timeval *start_eat, int elapsed)
{
	struct timeval	time;
	int				value;

	if (gettimeofday(&time, NULL))
		return (ERROR);
	value = time.tv_usec - start_eat->tv_usec;
	if (value < 0)
		value += 1000000;
	value /= N_TO_M;
	return (value >= elapsed);
}

void	time_update(t_philo *philo, struct timeval *time)
{
	philo->start_eat.tv_sec = time->tv_sec;
	philo->start_eat.tv_usec = time->tv_usec;
}

int	set_start_time(t_philo *philo, int num)
{
	int	i;

	if (gettimeofday(&(philo[0].start_eat), NULL))
		return (ERROR);
	i = 1;
	while (i < num)
	{
		philo[i].start_eat.tv_sec = philo[0].start_eat.tv_sec;
		philo[i].start_eat.tv_usec = philo[0].start_eat.tv_usec;
		++i;
	}
	return (SUCCESS);
}
