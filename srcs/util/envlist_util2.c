/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:37:36 by youlee            #+#    #+#             */
/*   Updated: 2021/01/15 02:42:48 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_str_de(void)
{
	int idx;
	int idx2;

	idx = 0;
	while (soenvl[idx][12])
	{
		ft_strlcpy(soenvl[idx], "declare -x", 11);
		soenvl[idx][10] = ' ';
		idx++;
	}
}

bool	check_env(char *find, char *b)
{
	int idx;

	idx = 0;
	while (find[idx])
	{
		if (find[idx] != b[idx])
			return (false);
		idx++;
	}
	if (find[idx] != '\0' || b[idx] != '=')
		return (false);
	return (true);
}
