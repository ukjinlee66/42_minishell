/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_relative_run.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:34:24 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 21:34:00 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				stat_check(int status)
{
	g_pid_stat = true;
	if (WIFEXITED(status) == false)
	{
		if (ft_strcmp(g_ret_str, "130") == 0)
			return (130);
		else if (ft_strcmp(g_ret_str, "131") == 0)
			return (131);
	}
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int				command_relative_run(char **argv, int *receiver, int *sender)
{
	int		status;
	char	*path;
	char	*command;
	char	**envp;
	int		pid;

	if (is_dir(&argv[0]) != 0)
		return (is_dir(&argv[0]));
	path = ft_strdup(argv[0] + 2);
	envp = make_envp();
	command = make_com(argv[0]);
	argv[0] = command;
	g_pid_stat = false;
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, argv, envp) == -1)
		{
			write(1, strerror(errno), ft_strlen(strerror(errno)) + 1);
			write(1, "\n", 1);
			exit(1);
		}
	}
	waitpid(pid, &status, 0);
	return (stat_check(status));
}
