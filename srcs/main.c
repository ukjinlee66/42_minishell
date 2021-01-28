/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 15:15:53 by youlee            #+#    #+#             */
/*   Updated: 2021/01/28 15:13:03 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		main_process(void)
{
	t_list			*command_lines;
	char			*line;
	int				gnl_ret;
	pid_t			pid_num;

	if ((gnl_ret = get_interactive_line(&line)) < 0)
		exit (2);			//unexpected case
	if (gnl_ret == 0)		//ctrl + D
	{
		write(1, "exit\n", 5);
		exit(0); // command_exit yet
	}
	if ((command_lines = split_line((const char *)line)))
	{
		/*
		t_list			*test;
		char			*test_str;

		test = command_lines;
		while (test)
		{
			test_str = (char *)test->data;
			printf("test for parsing: %s -> %lu\n", test_str, \
					ft_strlen((const char *)test_str));
			test = test->next;
		}
		*/
		int		receiver[1000];
		int		sender[1000];
		receiver[0] = -1;
		sender[0] = -1;
		ret_str = ft_strdup("0");
		handle_command(&command_lines, receiver, sender);
	}
}

int			main(int argc, char **argv, char **envp)
{
	if (argc == 1)
	{
		copy_env_list(envp); //envp -> envl copy
		while (1)
		{
			getcwd(cur_path, PATH_SIZE);
			write(1, cur_path, ft_strlen(cur_path));
			write(1, "$ ", 2);
			main_process();
		}
	}
	else
	{

	}
	return (0);
}
