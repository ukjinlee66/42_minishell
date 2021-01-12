/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 16:45:22 by youlee            #+#    #+#             */
/*   Updated: 2021/01/12 17:27:29 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_env_list(char **envp) //envp -> envl
{
	int		idx;
	int		idx2;

	idx = 0;
	idx2 = 0;
	while (envp[idx])
	{
		while (envp[idx][idx2])
		{
			envl[idx][idx2] = envp[idx][idx2];
			idx2++;
		}
		idx++;
	}
	envl_sort();
}

void	envl_sort(void)
{
	int		idx;
	int		idx2;
	char	*temp;

	idx = 0;
	while (envl[idx])
	{
		idx2 = 0;
		while (envl[idx2])
		{
			if (idx == idx2)
				idx2++;
			if (envl[idx][0] > envl[idx2][0])
			{
				temp = envl[idx];
				envl[idx] = envl[idx2];
				envl[idx2] = temp;

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
