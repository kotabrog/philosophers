/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   share.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 10:29:12 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/18 10:59:35 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	share_free(t_share *share)
{
	sem_close(share->sem);
	sem_close(share->fork_sem);
	sem_unlink(SEM_NAME_FORK);
	sem_unlink(SEM_NAME_DATA);
}

int	share_init(t_share *share, int fork_num)
{
	share->fork_sem = NULL;
	share->sem = sem_open(SEM_NAME_DATA, O_CREAT | O_EXCL, 0777, 1);
	if (share->sem == SEM_FAILED)
		return(ERROR);
	share->fork_sem = sem_open(SEM_NAME_FORK, \
								O_CREAT | O_EXCL, \
								0777, \
								fork_num);
	if (share->fork_sem == SEM_FAILED)
		return (ERROR);
	share->stop_flag = FALSE;
	share->stop_eat_count = 0;
	return (SUCCESS);
}
