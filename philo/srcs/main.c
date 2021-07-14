/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:55:00 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/14 20:36:06 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		debug_config(status);
	status_free(status, flag);
	return (!!flag);
}
