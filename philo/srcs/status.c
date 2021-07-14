/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:13:02 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/14 20:07:10 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	status_free(t_status *status, int flag)
{
	if (flag >= 0)
		free(status);
}

int	status_init(t_status **status)
{
	if (ft_malloc(status, sizeof(t_status), 1))
		return (ERROR);
	(*status)->philo = NULL;
	(*status)->fork = NULL;
	return (SUCCESS);
}
