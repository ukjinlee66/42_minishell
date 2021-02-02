/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:16:13 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 22:21:45 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		command_exit(char **argv)
{
	int ret;

	write(2, "exit\n", 5);
	if (!argv[1])
		exit(127);
	else
		ret = ft_atoi(argv[1]);
	exit(ret);
}
