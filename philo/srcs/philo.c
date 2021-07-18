/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 21:13:09 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/18 15:04:46 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_thread(t_philo *philo)
{
	int	flag;

	if (pthread_mutex_lock(&(philo->share->start)) || \
		pthread_mutex_unlock(&(philo->share->start)))
	{
		share_change_stop(philo->share, ERROR);
		return ;
	}
	if (philo->own_num % 2 == 0)
		usleep(100);
	flag = share_check_stop(philo->share);
	while (!flag)
	{
		if (eat(philo))
			break ;
		accurate_usleep(philo->cfg->time_sleep, philo->before_time);
		if (print_status(THINK, -1, philo, philo->share))
			break ;
		flag = share_check_stop(philo->share);
	}
}

int	philo_init(t_status *status)
{
	int	i;
	int	num;

	num = status->cfg.num_philo;
	if (ft_malloc(&(status->philo), sizeof(t_philo), num))
		return (ERROR);
	i = 0;
	while (i < num)
	{
		status->philo[i].own_num = i + 1;
		status->philo[i].cfg = &(status->cfg);
		status->philo[i].eat_count = 0;
		status->philo[i].share = &(status->share);
		status->philo[i].left_fork = &(status->fork[i]);
		status->philo[i].right_fork = &(status->fork[(i + 1) % num]);
		++i;
	}
	return (SUCCESS);
}
