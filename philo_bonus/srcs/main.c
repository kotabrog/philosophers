/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuzuki <ksuzuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 10:25:27 by ksuzuki           #+#    #+#             */
/*   Updated: 2021/07/18 10:56:13 by ksuzuki          ###   ########.fr       */
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
	status_free(status, flag);
	return (!!flag);
}
