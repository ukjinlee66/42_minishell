/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_excutable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:09:45 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 15:07:49 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		launch_excutable(char **argv, int *receiver, int *sender)
{
	char	**envp;
	int		pid;
	int		status;

	envp = make_envp();
	g_pid_stat = false;
	pid = fork();
	if (pid == 0)
	{
		if (!dir_err(NULL, argv, envp))
		{
			write(1, (*argv), ft_strlen(*argv) + 1);
			write(1, ": command not found\n", 21);
			exit(127);
			//return (127);
		}
		exit (0);
	}
	waitpid(pid, &status, 0);
	g_pid_stat = true;
	if (WIFEXITED(status) == false)
	{
		if (ft_strcmp(g_ret_str, "130") == 0)
			return (130);
		else if (ft_strcmp(g_ret_str, "131") == 0)
			return (131);
	}
	return (0);
}
