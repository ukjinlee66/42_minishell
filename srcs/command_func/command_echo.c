/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:15:59 by youlee            #+#    #+#             */
/*   Updated: 2020/11/13 20:20:56 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		command_echo(char **argv, int *receiver, int *sender)
{
	int cnt;
	char *res;
	char *temp;
	int fd;
	bool option_val;

	if (sender[0] == -1)
		fd = 1;
	else
		fd = 125; //임의의 값.
	cnt = 1;
	if (argv[1] == NULL) //단일 에코
		write(fd, "\n", 5);
	else
	{
		temp = ft_strjoin("", "");
		while (argv[cnt])
		{
			if ((ft_strcmp(argv[cnt],"-n") == 0))
			{
				option_val = true;
				cnt++;
				continue;
			}
			res = ft_strjoin(temp, argv[cnt]);
			ft_putstr_fd(argv[cnt], fd);
			if (argv[cnt + 1] != NULL)
				write(fd, " ", 1);
			free(temp);
			temp = res;
			cnt++;	
		}
		cnt = 0;
		//clean function two pointer
		two_pointer_free(&argv);
		if (option_val == false)
			write(fd, "\n", 1);
		//pipe add code
		free(temp);
	}
}

