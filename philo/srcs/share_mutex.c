/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share_mutex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 19:08:18 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/15 19:12:24 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	share_check_stop(t_share *share)
{
	int	flag;

	if (pthread_mutex_lock(&(share->stop_mutex)))
		return (ERROR);
	flag = share->stop_flag;
	if (pthread_mutex_unlock(&(share->stop_mutex)))
		return (ERROR);
	return (flag);
}

int	share_change_stop(t_share *share, int flag)
{
	if (pthread_mutex_lock(&(share->stop_mutex)))
		return (ERROR);
	share->stop_flag = flag;
	if (pthread_mutex_unlock(&(share->stop_mutex)))
		return (ERROR);
	return (SUCCESS);
}
