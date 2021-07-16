/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 19:08:18 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/16 22:37:58 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_one_philo(t_philo *philo, t_status *status)
{
	int				flag;
	struct timeval	time;
	int				value;

	if (pthread_mutex_lock(&(status->share.mutex)))
		return (ERROR);
	if (status->share.stop_flag)
		return (TRUE);
	if (gettimeofday(&time, NULL))
		flag = ERROR;
	else
	{
		value = time.tv_usec - philo->start_eat.tv_usec;
		if (value < 0)
			value += 1000000;
		flag = ((value / N_TO_M) >= status->cfg.time_die);
	}
	if (flag == TRUE)
	{
		status->share.stop_flag = TRUE;
		printf("%ld %d died\n", time.tv_usec / N_TO_M, philo->own_num);
	}
	else if (flag == ERROR)
		status->share.stop_flag = ERROR;
	if (pthread_mutex_unlock(&(status->share.mutex)))
		return (ERROR);
	return (flag);
}

void	check_die_thread(t_status *status)
{
	int		i;
	int		flag;

	flag = FALSE;
	i = 0;
	while (!flag)
	{
		flag = check_one_philo(&(status->philo[i]), status);
		if (!flag)
			flag = share_check_stop(&(status->share));
		i = (i + 1) % status->cfg.num_philo;
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
