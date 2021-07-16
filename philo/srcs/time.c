/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 11:34:57 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/16 11:37:03 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	time_update(t_philo *philo, struct timeval *time)
{
	philo->start_eat.tv_sec = time->tv_sec;
	philo->start_eat.tv_usec = time->tv_usec;
}
