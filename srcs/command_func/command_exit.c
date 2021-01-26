/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:16:13 by youlee            #+#    #+#             */
/*   Updated: 2021/01/26 20:13:08 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		command_exit(char **argv)
{
	int ret;

	ret = ft_atoi(argv[0]);
	write(1, "exit program\n", 5);
	//run ctrl - C
	return (ret);
}
