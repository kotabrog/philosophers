/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:15:01 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/15 18:28:09 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	share_free(t_share *share)
{
	pthread_mutex_destroy(&(share->stop_mutex));
	pthread_mutex_destroy(&(share->eat_count_mutex));
	pthread_mutex_destroy(&(share->print_mutex));
}

int	share_init(t_share *share)
{
	pthread_mutex_init(&(share->stop_mutex), NULL);
	pthread_mutex_init(&(share->eat_count_mutex), NULL);
	pthread_mutex_init(&(share->print_mutex), NULL);
	share->stop_flag = FALSE;
	share->stop_eat_count = 0;
	return (SUCCESS);
}
