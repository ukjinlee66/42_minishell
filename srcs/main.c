/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 15:15:53 by youlee            #+#    #+#             */
/*   Updated: 2021/02/01 22:03:18 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		main_process(void)
{
	t_list			*command_lines;
	char			*line;
	int				gnl_ret;
	int				receiver[1000];
	int				sender[1000];

			signal(SIGINT, handle_sig);
			signal(SIGQUIT, handle_sig2);
	getcwd(g_cur_path, PATH_SIZE);
	if (ft_strcmp(g_ret_str, "130") != 0)
	{
		printf("ret_str : %s\n",g_ret_str);
		write(1, g_cur_path, ft_strlen(g_cur_path));
		write(1, "$ ", 2);
	}
	if ((gnl_ret = get_interactive_line(&line)) < 0)
		exit(2);
	if (gnl_ret == 0)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if ((command_lines = split_line((const char *)line)))
	{
		receiver[0] = -1;
		sender[0] = -1;
		handle_command(&command_lines, receiver, sender);
	}
}

int			main(int argc, char **argv, char **envp)
{
	if (argc == 1)
	{
		g_ret_str = ft_strdup("0");
		copy_env_list(envp);
		g_pid_stat = true;
		while (1)
		{
			main_process();
		}
	}
	return (0);
}
