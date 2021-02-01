/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 19:58:39 by youlee            #+#    #+#             */
/*   Updated: 2021/02/01 13:12:35 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_env(char **argv, int *receiver, int *sender)
{
	int	idx;

	idx = 0;
	while (g_envl[idx])
	{
		if (g_envl[idx][0] == '\0')
			break ;
		write(1, g_envl[idx], ft_strlen(g_envl[idx]));
		write(1, "\n", 1);
		idx++;
	}
	return (0);
}
