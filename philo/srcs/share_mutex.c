/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 19:08:18 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/18 11:51:40 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_die(t_philo *philo, struct timeval *time)
{
	int	flag;

	flag = check_elapsed_time(philo->start_eat.tv_usec, time->tv_usec, \
		philo->cfg->time_die);
	if (flag == TRUE)
	{
		philo->share->stop_flag = TRUE;
		print_status_put(DIE, time->tv_usec, philo->own_num);
	}
	else if (flag == ERROR)
		philo->share->stop_flag = ERROR;
	return (flag);
}

void	check_die_thread(t_status *status)
{
	int				i;
	int				flag;
	struct timeval	time;

	flag = FALSE;
	while (!flag)
	{
		i = 0;
		usleep(N_TO_M / 2);
		if (pthread_mutex_lock(&(status->share.mutex)))
			return ;
		if (status->share.stop_flag)
			flag = TRUE;
		if (!flag && gettimeofday(&time, NULL))
			flag = ERROR;
		while (!flag && i < status->cfg.num_philo)
		{
			flag = check_philo_die(&(status->philo[i]), &time);
			++i;
		}
		if (pthread_mutex_unlock(&(status->share.mutex)))
			return ;
	}
}

int	share_check_stop(t_share *share)
{
	int	flag;

	if (pthread_mutex_lock(&(share->mutex)))
		return (ERROR);
	flag = share->stop_flag;
	if (pthread_mutex_unlock(&(share->mutex)))
		return (ERROR);
	return (flag);
}

int	share_change_stop(t_share *share, int flag)
{
	if (pthread_mutex_lock(&(share->mutex)))
		return (ERROR);
	share->stop_flag = flag;
	if (pthread_mutex_unlock(&(share->mutex)))
		return (ERROR);
	return (SUCCESS);
}
