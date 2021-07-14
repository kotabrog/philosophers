/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 19:47:33 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/14 19:51:35 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	debug_config(t_status *status)
{
	printf("--cfg--\n");
	printf("num_philo: %d\n", status->cfg.num_philo);
	printf("time_die: %d\n", status->cfg.time_die);
	printf("time_eat: %d\n", status->cfg.time_eat);
	printf("time_sleep: %d\n", status->cfg.time_sleep);
	printf("stop_eat_times: %d\n", status->cfg.stop_eat_times);
}
