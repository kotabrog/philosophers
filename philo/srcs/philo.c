/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 21:13:09 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/15 19:13:28 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	philo_thread(t_philo *philo)
{
	int	flag;

	flag = share_check_stop(philo->share);
	while (!flag)
	{
		if (print_status(philo->status, NULL, \
				&(philo->share->print_mutex), philo->own_num))
			share_change_stop(philo->share, ERROR);
		usleep(1000);
		flag = share_check_stop(philo->share);
	}
}

void	philo_free(t_philo *philo, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&(philo[i].status_mutex));
		++i;
	}
	free(philo);
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
		status->philo[i].status = THINK;
		pthread_mutex_init(&(status->philo[i].status_mutex), NULL);
		status->philo[i].share = &(status->share);
		status->philo[i].left_fork = &(status->fork[i]);
		status->philo[i].right_fork = &(status->fork[(i + 1) % num]);
		++i;
	}
	return (SUCCESS);
}
