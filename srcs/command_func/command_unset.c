/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 19:58:04 by youlee            #+#    #+#             */
/*   Updated: 2021/01/31 23:45:08 by youlee           ###   ########.fr       */
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
		while (envl[idx][0])
		{
			ft_strlcpy(envl[idx], envl[idx + 1],
					ft_strlen(envl[idx + 1]) + 1);
			idx++;
		}
		envl[idx - 1][0] = '\0';
		idx2 = get_soenv_list(argv[1]);
		while (soenvl[idx2][0])
		{
			ft_strlcpy(soenvl[idx2], soenvl[idx2 + 1],
					ft_strlen(soenvl[idx2 + 1]) + 1);
			idx2++;
		}
		soenvl[idx2 - 1][0] = '\0';
	}
	else
	{
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
		return (1);
	}
	return (0);
}

void	clear_soenvl(void)
{
	int	idx;

	idx = 0;
	while (soenvl[idx][0])
	{
		ft_memset(soenvl[idx], ' ', ft_strlen(soenvl[idx]));
		idx++;
	}
}
