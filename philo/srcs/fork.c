/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 20:56:18 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/14 21:03:22 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
