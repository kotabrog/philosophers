/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 11:17:45 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/17 11:10:29 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat_count(t_philo *philo, t_share *share)
{
	if (philo->eat_count < philo->cfg->stop_eat_times)
		philo->eat_count += 1;
	if (philo->eat_count == philo->cfg->stop_eat_times)
	{
		philo->eat_count += 1;
		share->stop_eat_count += 1;
		if (share->stop_eat_count == philo->cfg->num_philo)
			share->stop_flag = TRUE;
	}
}

static int	eat_end(t_philo *philo, t_share *share)
{
	int	flag;

	if (print_status(SLEEP, -1, philo, share))
		return (ERROR);
	flag = fork_release(philo->left_fork);
	if (!flag)
		flag = fork_release(philo->right_fork);
	if (flag == ERROR)
	{
		share_change_stop(share, ERROR);
		return (ERROR);
	}
	return (SUCCESS);
}

static int	eat_preparation(t_philo *philo, int is_left, t_share *share)
{
	int	flag;

	flag = FALSE;
	while (!flag)
	{
		flag = share_check_stop(share);
		if (flag)
			break ;
		if (is_left)
			flag = fork_take(philo->left_fork, philo, FALSE);
		else
			flag = fork_take(philo->right_fork, philo, TRUE);
	}
	if (flag == ERROR)
	{
		share_change_stop(share, ERROR);
		return (ERROR);
	}
	return (SUCCESS);
}

int	eat(t_philo *philo)
{
	if (eat_preparation(philo, TRUE, philo->share))
		return (ERROR);
	if (eat_preparation(philo, FALSE, philo->share))
		return (ERROR);
	usleep(N_TO_M * philo->cfg->time_eat);
	if (eat_end(philo, philo->share))
		return (ERROR);
	return (SUCCESS);
}
