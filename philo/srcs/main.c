/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:55:00 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/15 19:16:22 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	set_start_time(t_philo *philo, int num)
{
	int	i;

	if (gettimeofday(&(philo[0].start_eat), NULL))
		return (ERROR);
	i = 1;
	while (i < num)
	{
		philo[i].start_eat.tv_sec = philo[0].start_eat.tv_sec;
		philo[i].start_eat.tv_usec = philo[0].start_eat.tv_usec;
		++i;
	}
	return (SUCCESS);
}

static int	start_thread(t_status *status, t_philo *philo, int num)
{
	int	i;

	if (FALSE)
		printf("num_philo: %d\n", status->cfg.num_philo);
	i = 0;
	while (i < num)
	{
		if (pthread_create(&(philo[i].thread), NULL, \
				(void *)philo_thread, &(philo[i])))
			return (ERROR);
		++i;
	}
	return (SUCCESS);
}

static int	join_thread(t_status *status, t_philo *philo, int num)
{
	int	i;
	int	flag;

	flag = SUCCESS;
	usleep(5000);
	share_change_stop(&(status->share), TRUE);
	i = 0;
	while (i < num)
	{
		if (pthread_join(philo[i].thread, NULL))
			flag = ERROR;
		++i;
	}
	return (flag);
}

static int	start(t_status *status)
{
	int	flag;

	if (set_start_time(status->philo, status->cfg.num_philo))
		return (FREE_ALL);
	flag = start_thread(status, status->philo, status->cfg.num_philo);
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
