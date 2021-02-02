/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_relative_run.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:34:24 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 11:34:36 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

int		command_relative_run(char **argv, int *receiver, int *sender)
{
	int		idx;
	char	*path;
	char	*command;
	char	**envp;
	int		pid;

	path = ft_strdup(argv[0] + 2);
	envp = make_envp();
	command = make_com(argv[0]);
	argv[0] = command;
	idx = 0;
	pid = fork();
	if (pid == 0)
	{
		g_pid_stat = false;
		if (execve(path, argv, envp) == -1)
		{
			write(1, strerror(errno), ft_strlen(strerror(errno)) + 1);
			write(1, "\n", 1);
			exit(1);
			//return (1);
		}
	}
	wait(0);
	return (0);
}
