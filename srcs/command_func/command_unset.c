/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 19:58:04 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 17:56:54 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		command_unset(char **argv, int *receiver, int *sender)
{
	int	idx[2];

	idx[0] = get_env_list(argv[1]);
	if (idx[0])
	{
		idx[1] = idx[0];
		while (g_envl[idx[0]][0])
		{
			ft_strlcpy(g_envl[idx[0]], g_envl[idx[0] + 1],
					ft_strlen(g_envl[idx[0] + 1]) + 1);
			idx[0]++;
		}
		g_envl[idx[0] - 1][0] = '\0';
		idx[1] = get_soenv_list(argv[1]);
		while (g_soenvl[idx[1]][0])
		{
			ft_strlcpy(g_soenvl[idx[1]], g_soenvl[idx[1] + 1],
					ft_strlen(g_soenvl[idx[1] + 1]) + 1);
			idx[1]++;
		}
		g_soenvl[idx[1] - 1][0] = '\0';
	}
	else
		return (put_err((int)errno));
	return (0);
}

void	clear_soenvl(void)
{
	int	idx;

	idx = 0;
	while (g_soenvl[idx][0])
	{
		ft_memset(g_soenvl[idx], ' ', ft_strlen(g_soenvl[idx]));
		idx++;
	}
}
