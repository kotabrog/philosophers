/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:56:18 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/17 10:18:26 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_release(t_fork *one_fork)
{
	if (pthread_mutex_lock(&(one_fork->mutex)))
		return (ERROR);
	one_fork->use_flag = FALSE;
	if (pthread_mutex_unlock(&(one_fork->mutex)))
		return (ERROR);
	return (SUCCESS);
}

int	fork_take(t_fork *one_fork, t_philo *philo, int eat_flag)
{
	int	flag;

	flag = FALSE;
	if (pthread_mutex_lock(&(one_fork->mutex)))
		return (ERROR);
	if (!one_fork->use_flag)
	{
		one_fork->use_flag = TRUE;
		if (eat_flag)
			flag = print_status(FORK, EAT, philo, philo->share);
		else
			flag = print_status(FORK, -1, philo, philo->share);
		if (flag == SUCCESS)
			flag = TRUE;
	}
	if (pthread_mutex_unlock(&(one_fork->mutex)))
		return (ERROR);
	return (flag);
}

void	fork_free(t_fork *forks, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_destroy(&(forks[i].mutex));
		++i;
	}
	free(forks);
}

int	fork_init(t_fork **forks, int num)
{
	int	i;

	if (ft_malloc(forks, sizeof(t_fork), num))
		return (ERROR);
	i = 0;
	while (i < num)
	{
		(*forks)[i].use_flag = FALSE;
		pthread_mutex_init(&((*forks)[i].mutex), NULL);
		++i;
	}
	return (SUCCESS);
}
