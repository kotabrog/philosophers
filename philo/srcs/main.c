/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:55:00 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/16 22:59:28 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_thread(t_status *status, t_philo *philo, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (pthread_create(&(philo[i].thread), NULL, \
				(void *)philo_thread, &(philo[i])))
			return (ERROR);
		++i;
	}
	if (pthread_create(&(status->thread), NULL, \
			(void *)check_die_thread, status))
		return (ERROR);
	return (SUCCESS);
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

	if (set_start_time(status->philo, status->cfg.num_philo))
		return (FREE_ALL);
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
