/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:21:57 by youlee            #+#    #+#             */
/*   Updated: 2020/11/02 20:23:31 by youlee           ###   ########.fr       */
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
		return (0);		//malloc fail
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
	pid_t		pid_num;
	int cnt;
	char		buf[IO_BUF_SIZE];

	argv = construct_argv(list_start, list_end);
	if (!(pid_num = fork()))//child
	{
		if (!ft_strcmp(argv[0], "echo"))
			command_echo(argv, receiver, sender);
		else if (!ft_strcmp(argv[0], "cd"))
			command_cd(argv, receiver, sender);
		else if (!ft_strcmp(argv[0], "pwd"))
			command_pwd(argv, receiver, sender);
		else if (!ft_strcmp(argv[0], "export"))
			command_export(argv, receiver, sender);
		else if (!ft_strcmp(argv[0], "unset"))
			command_unset(argv, receiver, sender);
		else if (!ft_strcmp(argv[0], "env"))
			command_env(argv, receiver, sender);
		else if (!ft_strcmp(argv[0], "exit"))
			command_exit();
		else if (argv[0][0] == '.' && argv[0][1] =='/')
			command_relative_run(argv, receiver, sender);
		else
			launch_excutable(argv, receiver, sender); //error case	
	}
	else//parent
	{
		cnt = 0;
		//while (receiver[cnt])
		//	read(receiver[cnt++],buf, IO_BUF_SIZE);

	}

	int			read_len;

	cnt = 0;
	write(1, "command: ", 9);
	while (argv[cnt])
	{
		write(1, argv[cnt], ft_strlen((const char *)argv[cnt]));
		write(1, " ", 1);
		cnt++;
	}
	write(1, "\n", 1);

	cnt = 0;
	while (argv[cnt])
	{
		free(argv[cnt]);
		cnt++;
	}
	free(argv);

	cnt = 0;
	while (receiver[cnt] != -1)
	{
		read_len = read(receiver[cnt], buf, IO_BUF_SIZE);
		buf[read_len] = 0;
		write(1, "test input: ", 12);
		write(1, buf, read_len);
		write(1, "\n", 1);
		cnt++;
	}

	cnt = 0;
	while (sender[cnt] != -1)
	{
		write(sender[cnt], "test output", 11);
		cnt++;
	}
	return (0);
}
