/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_absolute_run.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 05:45:28 by youlee            #+#    #+#             */
/*   Updated: 2021/01/19 05:47:27 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_absolute_run(char **argv, int *receiver, int *sender)
{
	int		idx;
	char	*path;
	char	*command;
	char	**envp;

	path = ft_strdup(argv[0] + 1);
	envp = make_envp();
	command = make_com(argv[0]);
	argv[0] = command;
	idx = 0;
	if (execve(path, argv, envp) == -1)
		printf("execve error\n");
	else
		printf("execve run!\n");	
}

char	*make_com(char *argv)
{
	char	*ret;
	int		size;

	size = ft_strlen(argv);
	while (size--)
		if (argv[size] == '/')
			break;
	ret = ft_strdup(argv + size + 1);
	return (ret);
}

char	**make_envp(void)
{
	char	**temp;
	int		idx;

	idx = 0;
	while (envl[idx][0])
		idx++;
	temp = (char**)malloc(sizeof(char*) * (idx + 1));
	idx = 0;
	while (envl[idx][0])
	{
		temp[idx] = ft_strdup(envl[idx]);
		printf("temp[idx] : %s\n", envl[idx]);
		idx++;
	}
	temp[idx] = 0;
	return (temp);
}
