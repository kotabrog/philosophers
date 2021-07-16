/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 11:34:57 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/16 22:12:38 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
