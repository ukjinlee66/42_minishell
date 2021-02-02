/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_excutable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:09:45 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 14:05:26 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		launch_excutable(char **argv, int *receiver, int *sender)
{
	char	**envp;
	int		pid;

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
	}
	wait(0);
	g_pid_stat = true;
	return (0);
}
