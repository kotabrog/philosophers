/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:15:01 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/18 15:03:24 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	share_free(t_share *share)
{
	pthread_mutex_destroy(&(share->mutex));
	pthread_mutex_destroy(&(share->start));
}

int	share_init(t_share *share)
{
	pthread_mutex_init(&(share->mutex), NULL);
	pthread_mutex_init(&(share->start), NULL);
	share->stop_flag = FALSE;
	share->stop_eat_count = 0;
	return (SUCCESS);
}
