/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 15:15:53 by youlee            #+#    #+#             */
/*   Updated: 2020/09/12 16:18:14 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		main_process(void)
{
	t_list			*inputs;
	char			*line;
	int				gnl_ret;

	if ((gnl_ret = get_interactive_line(&line)) < 0)
		exit (2);			//unexpected case
	if (gnl_ret == 0)		//ctrl + D
		command_exit();
	if ((inputs = split_line((const char *)line)))
	{
		free(line);
		line = 0;

		//for test
		t_list			*test;
		char			*test_str;

		test = inputs;
		while (test)
		{
			test_str = (char *)test->data;
			printf("test for parsing: %s -> %lu\n", test_str, \
					ft_strlen((const char *)test_str));
			test = test->next;
		}
		//for test
		free_list(inputs);
	}
}

int			main(void)
{
	char			path[PATH_SIZE];

	while (1)
	{
		getcwd(path, PATH_SIZE);
		write(1, path, ft_strlen(path));
		write(1, "$ ", 2);
		main_process();
	}
	return (0);
}
