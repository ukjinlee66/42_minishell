/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 20:21:57 by youlee            #+#    #+#             */
/*   Updated: 2021/01/30 03:42:41 by youlee           ###   ########.fr       */
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
	int			cnt;
	char		buf[IO_BUF_SIZE];
	int			ret;

	ret = 0;
	argv = construct_argv(list_start, list_end);
	printf("\nmy pid : %d\n",getpid());
	int i = -1;
	while (sender[i++] != -1)
		printf("sender[%d] : %d\n",i,sender[i]);
	i = -1;
	while (receiver[i++] != -1)
		printf("receiver[%d] : %d\n",i,receiver[i]);
	if (argv[0] != 0)
	{
		
		if (receiver[0] != -1 && sender[0] == -1) //last process
		{
			dup2(receiver[0], 0); //표준 입력 치환
			//close(sender[0]);
			//read(receiver[0], print_buf, 1000);
			//printf("last print buf : %s\n",print_buf);
			//close(receiver[1]);
			//close(receiver[0]);
		}
		else if (sender[0] != -1 && receiver[0] == -1)//first process
		{
			//close(test);
			//dup2(0, test);
			dup2(sender[0], 1); //표준 출력 치환
			//close(receiver[0]);
			//close(sender[1]);
			//close(sender[0]);
		}
		else if (sender[0] != -1 && receiver[0] != -1)//mid process
		{
			dup2(sender[0], 1);
			dup2(receiver[0], 0);
			//read(receiver[0], print_buf, 1000);
			//printf("\nmid print buf : %s\n",print_buf);
			//close(receiver[1]);
			//close(sender[1]);
			//close(receiver[0]);
			//close(sender[0]);
			
		}
		//int test = open("dummy", O_WRONLY | O_CREAT);
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
			ret = launch_excutable(argv, receiver, sender); //error case	
		//if (sender[0] != -1 && receiver[0] != -1)
		//	dup2(test, 0);
	}
	//if (sender[0] != -1) //pipe out data
	//	write(sender[0], print_buf, ft_strlen(print_buf) + 1);
	ret_str = ft_itoa(ret);
	two_pointer_free(&argv);
	if (sender[0] == -1) // 마지막명령일경우
	{
		//printf("run kill!\n");
		//kill(0, SIGKILL);
	}
	
	/*
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
	*/
	printf("ret string : %s\n",ret_str);
	return (ret);
}
