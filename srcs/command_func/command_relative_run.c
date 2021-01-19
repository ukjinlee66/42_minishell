/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_relative_run.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 19:58:55 by youlee            #+#    #+#             */
/*   Updated: 2021/01/20 02:36:35 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"


void	command_relative_run(char **argv, int *receiver, int *sender)
{
	int		idx;
	char	*path;
	char	*command;
	char	**envp;

	path = ft_strdup(argv[0] + 2);
	envp = make_envp();
	command = make_com(argv[0]);
	argv[0] = command;
	idx = 0;
	if (execve(path, argv, envp) == -1)
		printf("execve relative error\n");
	else
		printf("execve run!\n");
}
