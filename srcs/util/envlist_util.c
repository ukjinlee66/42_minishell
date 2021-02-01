/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:45:22 by youlee            #+#    #+#             */
/*   Updated: 2021/02/01 13:20:14 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_arr(char *a, char *b, int num)
{
	int		i;

	i = 0;
	while (i < num)
	{
		a[i] = ' ';
		i++;
	}
	i = 0;
	while (b[i])
	{
		a[i + num] = b[i];
		i++;
	}
	a[i + num] = '\0';
}

void	copy_env_list(char **envp)
{
	int		idx;
	char	temp[2048];

	idx = 0;
	while (envp[idx])
	{
		copy_arr(g_envl[idx], envp[idx], 0);
		idx++;
	}
	g_envl[idx][0] = '\0';
	envl_sort();
}

void	copy_env_list2(char env[2048][2048],
		char env2[2048][2048])
{
	int		idx;
	char	temp[2048];

	idx = 0;
	while (env2[idx][0])
	{
		copy_arr(env[idx], env2[idx], 11);
		add_double(&env[idx]);
		idx++;
	}
	env[idx][0] = env2[idx][0];
}

void	envl_sort(void)
{
	int		idx;
	int		idx2;
	char	temp[2048];

	copy_env_list2(g_soenvl, g_envl);
	idx = 0;
	while (g_soenvl[idx][11])
	{
		idx2 = 0;
		while (g_soenvl[idx2][11])
		{
			if (idx == idx2)
				idx2++;
			if (g_soenvl[idx][11] < g_soenvl[idx2][11])
			{
				copy_arr(temp, g_soenvl[idx], 0);
				copy_arr(g_soenvl[idx], g_soenvl[idx2], 0);
				copy_arr(g_soenvl[idx2], temp, 0);
			}
			idx2++;
		}
		idx++;
	}
	add_str_de();
}

int		get_env_list(char *chr)
{
	int idx;

	idx = 0;
	while (g_envl[idx][0])
	{
		if (check_env(chr, g_envl[idx]))
			return (idx);
		idx++;
	}
	return (-1);
}
