/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:55:00 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/18 15:07:16 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_thread(t_status *status, t_philo *philo, int num)
{
	int	i;
	int	flag;

	i = 0;
	flag = SUCCESS;
	if (pthread_mutex_lock(&(status->share.start)))
		return (ERROR);
	while (!flag && i < num)
	{
		if (pthread_create(&(philo[i].thread), NULL, \
				(void *)philo_thread, &(philo[i])))
			flag = ERROR;
		++i;
	}
	if (!flag && set_start_time(status->philo, status->cfg.num_philo))
		flag = ERROR;
	if (!flag && pthread_create(&(status->thread), NULL, \
		(void *)check_die_thread, status))
		return (ERROR);
	if (pthread_mutex_unlock(&(status->share.start)))
		return (ERROR);
	return (flag);
}

static int	join_thread(t_status *status, t_philo *philo, int num)
{
	int	i;
	int	flag;

	flag = SUCCESS;
	i = 0;
	while (i < num)
	{
		if (pthread_join(philo[i].thread, NULL))
			flag = ERROR;
		++i;
	}
	if (pthread_join(status->thread, NULL))
		flag = ERROR;
	return (flag);
}

static int	start(t_status *status)
{
	int	flag;

	flag = start_thread(status, status->philo, status->cfg.num_philo);
	if (flag)
		share_change_stop(&(status->share), ERROR);
	if (join_thread(status, status->philo, status->cfg.num_philo) || flag)
		return (FREE_ALL);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_status	*status;
	int			flag;

	if (status_init(&status))
		return (EXIT_FAILURE);
	flag = arg_parse(status, argc, argv);
	if (!flag)
		flag = status_set(status);
	if (!flag)
		flag = start(status);
	status_free(status, flag);
	return (!!flag);
}
