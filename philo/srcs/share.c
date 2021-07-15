/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:15:01 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/15 21:36:41 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	share_free(t_share *share)
{
	pthread_mutex_destroy(&(share->mutex));
}

int	share_init(t_share *share)
{
	pthread_mutex_init(&(share->mutex), NULL);
	share->stop_flag = FALSE;
	share->stop_eat_count = 0;
	return (SUCCESS);
}
