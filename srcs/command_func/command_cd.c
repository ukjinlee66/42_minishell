/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 19:57:26 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 17:27:18 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		command_cd(char **argv, int *receiver, int *sender)
{
	if (argv[1])
	{
		if ((g_dp = opendir(argv[1])) == NULL)
		{
			write(1, strerror(errno), ft_strlen(strerror(errno)) + 1);
			write(1, "\n", 1);
			return (1);
		}
		else
		{
			chdir(argv[1]);
			getcwd(g_cur_path, PATH_SIZE);
		}
	}
	else
		return (cd_home());
	return (0);
}

int		cd_home(void)
{
	char	**name_value;
	char	path[2048];
	int		idx;

	if ((idx = get_env_list("HOME")) == -1)
	{
		write(1, "HOME not set\n", 13);
		return (1);
	}
	name_value = ft_split(g_envl[idx], '=');
	if ((g_dp = opendir(name_value[1])) == NULL)
	{
		write(1, strerror(errno), ft_strlen(strerror(errno)) + 1);
		write(1, "\n", 1);
		return (1);
	}
	else
	{
		chdir(name_value[1]);
		getcwd(g_cur_path, PATH_SIZE);
	}
	free(name_value[0]);
	free(name_value[1]);
	free(name_value);
	return (0);
}
