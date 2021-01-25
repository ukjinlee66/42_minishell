/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 19:57:26 by youlee            #+#    #+#             */
/*   Updated: 2021/01/26 02:07:54 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	command_cd(char **argv, int *receiver, int *sender)
{
	if (argv[1])
	{
		if ((dp = opendir(argv[1])) == NULL) //error case
		{
			write(1, strerror(errno), ft_strlen(strerror(errno)) + 1);
			write(1, "\n", 1);
		}
		else
		{
			chdir(argv[1]);
			getcwd(cur_path, PATH_SIZE); //current path
		}
	}
	else
	{
		cd_home();
	}
}

void	cd_home(void)
{
	char	**name_value;
	char	path[2048];
	int		idx;

	if ((idx = get_env_list("HOME")) == -1)
	{
		write(1, "HOME not set\n", 13);
		return ;
	}
	name_value = ft_split(envl[idx], '=');
	if ((dp = opendir(name_value[1])) == NULL) //error case
	{
		write(1, strerror(errno), ft_strlen(strerror(errno)) + 1);
		write(1, "\n", 1);
	}
	else
	{
		getcwd(cur_path, PATH_SIZE); //current path
		chdir(name_value[1]);
		getcwd(cur_path, PATH_SIZE); //current path
	}
	free(name_value);
}
