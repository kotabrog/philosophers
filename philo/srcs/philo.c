/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 21:13:09 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/17 11:10:48 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_thread(t_philo *philo)
{
	int	flag;

	flag = share_check_stop(philo->share);
	while (!flag)
	{
		if (eat(philo))
			break ;
		usleep(N_TO_M * philo->cfg->time_sleep);
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
