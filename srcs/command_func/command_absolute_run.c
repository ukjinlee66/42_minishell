/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_absolute_run.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 05:45:28 by youlee            #+#    #+#             */
/*   Updated: 2021/02/01 21:31:02 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		command_absolute_run(char **argv, int *receiver, int *sender)
{
	int		idx;
	char	*path;
	char	*command;
	char	**envp;
	int		pid;

	path = ft_strdup(argv[0]);
	envp = make_envp();
	command = make_com(argv[0]);
	argv[0] = command;
	pid = fork();
	if (pid == 0)
	{
		g_pid_stat = false;
		if (!dir_err(&path, argv, envp))
		{
			free(path);
			return (put_err(errno));
		}
	}
	//idx = 0;
//	pid = fork();
//	if (pid == 0)
//	{
//		g_pid_stat = false;
//		if (execve(path, argv, envp) == -1)
//		{
//			free(path);
//			return (put_err(errno));
//		}
//	}
	return (0);
}

int		put_err(int errno)
{
	write(1, strerror(errno), ft_strlen(strerror(errno)) + 1);
	write(1, "\n", 1);
	return (1);
}

char	*make_com(char *argv)
{
	char	*ret;
	int		size;

	size = ft_strlen(argv);
	while (size--)
		if (argv[size] == '/')
			break ;
	ret = ft_strdup(argv + size + 1);
	return (ret);
}

char	**make_envp(void)
{
	char	**temp;
	int		idx;

	idx = 0;
	while (g_envl[idx][0] != '\0')
		idx++;
	temp = (char**)malloc(sizeof(char*) * (idx + 1));
	idx = 0;
	while (g_envl[idx][0] != '\0')
	{
		temp[idx] = ft_strdup(g_envl[idx]);
		idx++;
	}
	temp[idx] = NULL;
	return (temp);
}
