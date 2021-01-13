/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:45:22 by youlee            #+#    #+#             */
/*   Updated: 2021/01/13 23:54:27 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_arr(char *a, char *b)
{
	int i;

	i = 0;
	while (b[i])
	{
		a[i] = b[i];
		i++;
	}
	a[i]='\0';
}

void	copy_env_list(char **envp) //envp -> envl
{
	int		idx;
	char	temp[2048];

	idx = 0;
	while (envp[idx])
	{
		copy_arr(envl[idx], envp[idx]);
		idx++;
	}
	envl[idx][0] = '\0';
	envl_sort();
}

void	copy_env_list2(char env[2048][2048],
		char env2[2048][2048])
{
	printf("copy env list2\n");
	int		idx;
	char	temp[2048];

	idx = 0;
	while (env2[idx][0])
	{
		copy_arr(env[idx], env2[idx]);
		idx++;
	}
	env[idx][0] = '\0';
}

void	envl_sort(void)
{
	int		idx;
	int		idx2;
	char	temp[2048];

	copy_env_list2(soenvl, envl);
	idx = 0;
	while (soenvl[idx][0])
	{
		idx2 = 0;
		while (soenvl[idx2][0])
		{
			if (idx == idx2)
				idx2++;
			if (soenvl[idx][0] < soenvl[idx2][0])
			{
				copy_arr(temp, soenvl[idx]);
				copy_arr(soenvl[idx], soenvl[idx2]);
				copy_arr(soenvl[idx2], temp);
			}
			idx2++;
		}
		idx++;
	}
}

int		get_env_list(char *chr)
{
	int idx;

	idx = 0;
	while (envl[idx])
	{
		if(!ft_strcmp(chr, envl[idx])) //find chr
		{
			return(idx);
		}
		idx++;
	}
	return(-1);
}
