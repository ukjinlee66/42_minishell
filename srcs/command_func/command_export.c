/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:38:22 by youlee            #+#    #+#             */
/*   Updated: 2021/02/01 13:13:16 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		no_input(void)
{
	int		idx;

	idx = 0;
	while (g_soenvl[idx])
	{
		if (g_soenvl[idx][0] == '\0')
			break ;
		write(1, g_soenvl[idx], ft_strlen(g_soenvl[idx]));
		write(1, "\n", 1);
		idx++;
	}
}

int				command_export(char **argv, int *receiver, int *sender)
{
	char	**name_value;

	if (!argv[1])
		no_input();
	else
	{
		name_value = ft_split(argv[1], '=');
		if (get_env_list(name_value[0]) != -1)
		{
			set_env_list2(name_value[0], name_value[1]);
			envl_sort();
		}
		else
		{
			set_env_list(name_value[0], name_value[1]);
			envl_sort();
		}
		free(name_value[0]);
		free(name_value[1]);
		free(name_value);
	}
	return (0);
}
