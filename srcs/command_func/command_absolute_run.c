/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_absolute_run.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 05:45:28 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 22:03:29 by youlee           ###   ########.fr       */
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

	if ((pid = is_dir(&argv[0])))
		return (pid);
	path = ft_strdup(argv[0]);
	envp = make_envp();
	command = make_com(argv[0]);
	argv[0] = command;
	g_pid_stat = false;
	pid = fork();
	if (pid == 0)
	{
		if (!dir_err(&path, argv, envp))
		{
			free(path);
			exit(put_err((int)errno));
		}
		exit(0);
	}
	g_pid_stat = true;
	return (0);
}

int		is_dir(char **argv)
{
	if ((g_dp = opendir(argv[0])) != NULL)
	{
		write(1, argv[0], ft_strlen(argv[0]) + 1);
		write(1, ": is a directory\n", 18);
		return (126);
	}
	return (0);
}

int		put_err(int errn)
{
	write(1, strerror(errn), ft_strlen(strerror(errn)) + 1);
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
