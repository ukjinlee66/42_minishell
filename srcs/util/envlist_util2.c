/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlist_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 00:37:36 by youlee            #+#    #+#             */
/*   Updated: 2021/01/14 22:44:27 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_str_de(void)
{
	int idx;
	int idx2;
	char *temp;

	idx = 0;
	while (soenvl[idx][12])
	{
		write(1, soenvl[idx], ft_strlen(soenvl[idx]));
		write(1, "\n", 1);
		idx++;
	}
	idx = 0;
	temp = malloc(sizeof(char) * 12);
	temp = "declare -x ";
	printf("temp : %s\n",temp);
	while (soenvl[idx][12])
	{
		idx2 = 0;
		while (idx2 < 12)
		{
			soenvl[idx][idx2] = temp[idx2];
			idx2++;
		}
		idx++;
	}
	free(temp);
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
