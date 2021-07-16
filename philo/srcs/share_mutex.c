/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 19:08:18 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/16 19:45:49 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_die_thread(t_status *status)
{
	int		i;
	int		flag;
	t_philo	*philo;

	flag = FALSE;
	i = 0;
	while (!flag)
	{
		philo = &(status->philo[i]);
		flag = time_passed_check(&(philo->start_eat), status->cfg.time_die);
		if (flag == TRUE)
			print_status(DIE, -1, philo, &(status->share));
		else if (flag == ERROR)
			share_change_stop(&(status->share), ERROR);
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
