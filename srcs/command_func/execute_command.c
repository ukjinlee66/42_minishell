/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:21:57 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 15:11:46 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**construct_argv(t_list *list_start, t_list *list_end)
{
	int			cnt;
	t_list		*temp;
	char		**new_argv;

	cnt = 0;
	temp = list_start;
	while (temp != list_end)
	{
		temp = temp->next;
		cnt++;
	}
	if (!(new_argv = (char **)malloc(sizeof(char *) * (cnt + 1))))
		return (0);
	cnt = 0;
	while (list_start != list_end)
	{
		temp = list_start;
		list_start = list_start->next;
		new_argv[cnt] = (char *)temp->data;
		free(temp);
		cnt++;
	}
	new_argv[cnt] = 0;
	return (new_argv);
}

int			execute_command(t_list *list_start, t_list *list_end, \
								int *receiver, int *sender)
{
	char		**argv;
	int			cnt;
	char		buf[IO_BUF_SIZE];
	int			ret;
	int			tmp_fd, tmp_fd2;

	ret = 0;
	if (!(argv = construct_argv(list_start, list_end)))
	{
		free_list(list_start);
		return (2); // malloc failed
	}
	if (argv[0] != 0)
	{
		if (receiver[0] != -1 && sender[0] == -1)
		{
			tmp_fd = dup(0);
			dup2(receiver[0], 0);
		}
		else if (sender[0] != -1 && receiver[0] == -1)
		{
			tmp_fd = dup(1);
			dup2(sender[0], 1);
		}
		else if (sender[0] != -1 && receiver[0] != -1)
		{
			tmp_fd = dup(0);
			tmp_fd2 = dup(1);
			dup2(sender[0], 1);
			dup2(receiver[0], 0);
		}
		argv[0] = uppercase_conversion(argv[0]);
		if (!ft_strcmp(argv[0], "echo"))
			ret = command_echo(argv, receiver, sender);
		else if (!ft_strcmp(argv[0], "cd"))
			ret = command_cd(argv, receiver, sender);
		else if (!ft_strcmp(argv[0], "pwd"))
			ret = command_pwd(argv, receiver, sender);
		else if (!ft_strcmp(argv[0], "export"))
			ret = command_export(argv, receiver, sender);
		else if (!ft_strcmp(argv[0], "unset"))
			ret = command_unset(argv, receiver, sender);
		else if (!ft_strcmp(argv[0], "env"))
			ret = command_env(argv, receiver, sender);
		else if (!ft_strcmp(argv[0], "exit"))
			exit(1);
		else if (argv[0][0] == '/')
			ret = command_absolute_run(argv, receiver, sender);
		else if (argv[0][0] == '.' && argv[0][1] == '/')
			ret = command_relative_run(argv, receiver, sender);
		else
			ret = launch_excutable(argv, receiver, sender);
		if (sender[0] != -1 && receiver[0] == -1)
		{
			close(sender[0]);
			dup2(tmp_fd, 1);
		}
		else if (receiver[0] != -1 && sender[0] == -1)
		{
			close(receiver[0]);
			dup2(tmp_fd, 0);
		}
		else if (sender[0] != -1 && receiver[0] != -1)
		{
			close(sender[0]);
			close(receiver[0]);
			dup2(tmp_fd, 0);
			dup2(tmp_fd2, 1);
		}
	}
	ft_strlcpy(g_ret_str, ft_itoa(ret), ft_strlen(ft_itoa(ret)) + 2);
	two_pointer_free(&argv);
	return (ret);
}
