/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 19:29:48 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/17 11:17:58 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	arg_error(void)
{
	ft_putendl_fd("The argument given is incorrect.", 2);
	return (FREE_STATUS);
}

static int	set_int(char **str, int *num)
{
	int	i;

	*num = 0;
	i = 0;
	if (**str == '0' && ft_isdigit((*str)[1]))
		return (ERROR);
	while (ft_isdigit(**str))
	{
		if (i > 8)
			return (ERROR);
		else
			*num = *num * 10 + (**str - '0');
		++(*str);
		++i;
	}
	return (SUCCESS);
}

static int	set_number(char *str, int *num)
{
	*num = 0;
	if (set_int(&str, num))
		return (ERROR);
	if (*num == 0 || *str)
		return (ERROR);
	return (SUCCESS);
}

static int	arg_value_check(t_config *cfg)
{
	if (cfg->num_philo <= 1 || \
		cfg->num_philo >= 1000 || \
		cfg->time_die >= 1000 || \
		cfg->time_eat >= 1000 || \
		cfg->time_sleep >= 1000)
		return (ERROR);
	return (SUCCESS);
}

int	arg_parse(t_status *status, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (arg_error());
	if (set_number(argv[1], &(status->cfg.num_philo)) || \
		set_number(argv[2], &(status->cfg.time_die)) || \
		set_number(argv[3], &(status->cfg.time_eat)) || \
		set_number(argv[4], &(status->cfg.time_sleep)))
		return (arg_error());
	if (arg_value_check(&(status->cfg)))
		return (arg_error());
	if (argc == 6)
	{
		if (set_number(argv[5], &(status->cfg.stop_eat_times)))
			return (arg_error());
	}
	else
		status->cfg.stop_eat_times = -1;
	return (SUCCESS);
}
