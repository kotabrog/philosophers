/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:13:02 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/14 20:34:41 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	status_free(t_status *status, int flag)
{
	if (flag == SUCCESS || flag >= FREE_SHARE)
		share_free(&(status->share));
	free(status);
}

int	status_set(t_status *status)
{
	if (share_init(&(status->share)))
		return (FREE_SHARE);
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
