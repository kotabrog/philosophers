/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:13:02 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/15 18:28:31 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	status_free(t_status *status, int flag)
{
	if (flag == SUCCESS || flag >= FREE_SHARE)
	{
		if (status->share.stop_flag == ERROR)
			printf("unexpected error\n");
		share_free(&(status->share));
	}
	if (flag == SUCCESS || flag >= FREE_FORK)
		fork_free(status->fork, status->cfg.num_philo);
	if (flag == SUCCESS || flag == FREE_ALL)
		philo_free(status->philo, status->cfg.num_philo);
	free(status);
}

int	status_set(t_status *status)
{
	if (share_init(&(status->share)))
		return (FREE_SHARE);
	if (fork_init(&(status->fork), status->cfg.num_philo))
		return (FREE_SHARE);
	if (philo_init(status))
		return (FREE_FORK);
	return (SUCCESS);
}

int	status_init(t_status **status)
{
	if (ft_malloc(status, sizeof(t_status), 1))
		return (ERROR);
	(*status)->philo = NULL;
	(*status)->fork = NULL;
	return (SUCCESS);
}
