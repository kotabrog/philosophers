/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 20:13:02 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/13 20:47:55 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	status_init(t_status *status)
{
	if (ft_malloc(&status, sizeof(t_status), 1))
		return (ERROR);
	status->philo = NULL;
	status->fork = NULL;
}