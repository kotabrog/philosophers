/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 14:55:00 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/14 20:04:53 by ksuzuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_status	*status;
	int			flag;

	flag = SUCCESS;
	if (status_init(&status))
		return (EXIT_FAILURE);
	if (arg_parse(status, argc, argv))
		flag = FREE_STATUS;
	if (!flag)
		debug_config(status);
	status_free(status, flag);
	return (!!flag);
}
