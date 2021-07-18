/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 10:26:06 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/18 10:55:26 by ksuzuki          ###   ########.fr       */
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
	if (flag == SUCCESS || flag == FREE_ALL)
		free(status->philo);
	free(status);
}

int	status_set(t_status *status)
{
	if (share_init(&(status->share), status->cfg.num_philo))
		return (FREE_SHARE);
	if (philo_init(status))
		return (FREE_SHARE);
	return (SUCCESS);
}

int	status_init(t_status **status)
{
	if (ft_malloc(status, sizeof(t_status), 1))
		return (ERROR);
	(*status)->philo = NULL;
	return (SUCCESS);
}
