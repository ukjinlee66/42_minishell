/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:38:22 by youlee            #+#    #+#             */
/*   Updated: 2021/01/26 01:26:55 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	command_export(char **argv, int *receiver, int *sender)
{
	char **name_value;
	int	idx;
	
	idx = 0;
	if (!argv[1])
	{
		while (soenvl[idx])
		{
			if (soenvl[idx][0] == '\0') 
				break;
			write(1, soenvl[idx], ft_strlen(soenvl[idx]));
			write(1, "\n", 1);
			idx++;
		}
	}
	else //input case
	{
		name_value = ft_split(argv[1], '=');
		if (get_env_list(name_value[0]) != -1) //overlap check
		{
			set_env_list2(name_value[0], name_value[1]);
			envl_sort();
			free(name_value);
			return ;
		}
		set_env_list(name_value[0], name_value[1]);
		envl_sort();
		free(name_value);
	}
}
