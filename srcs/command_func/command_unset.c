/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 19:58:04 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 17:39:28 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		command_unset(char **argv, int *receiver, int *sender)
{
	int	idx;
	int	idx2;

	idx = get_env_list(argv[1]);
	if (idx)
	{
		idx2 = idx;
		while (g_envl[idx][0])
		{
			ft_strlcpy(g_envl[idx], g_envl[idx + 1],
					ft_strlen(g_envl[idx + 1]) + 1);
			idx++;
		}
		g_envl[idx - 1][0] = '\0';
		idx2 = get_soenv_list(argv[1]);
		while (g_soenvl[idx2][0])
		{
			ft_strlcpy(g_soenvl[idx2], g_soenvl[idx2 + 1],
					ft_strlen(g_soenvl[idx2 + 1]) + 1);
			idx2++;
		}
		g_soenvl[idx2 - 1][0] = '\0';
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
