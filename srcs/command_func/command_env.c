/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 19:58:39 by youlee            #+#    #+#             */
/*   Updated: 2021/01/31 23:30:49 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_env(char **argv, int *receiver, int *sender)
{
	int	idx;

	idx = 0;
	while (envl[idx])
	{
		if (envl[idx][0] == '\0')
			break ;
		write(1, envl[idx], ft_strlen(envl[idx]));
		write(1, "\n", 1);
		idx++;
	}
	return (0);
}
