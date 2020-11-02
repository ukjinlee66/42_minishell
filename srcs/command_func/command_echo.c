/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:15:59 by youlee            #+#    #+#             */
/*   Updated: 2020/11/02 21:51:58 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		command_echo(char **argv, int *receiver, int *sender)
{
	int cnt;
	char *res;
	char *temp;
	int fd;
	bool option;

	if (sender[0] == -1)
		fd = 1;
	else
		fd = 125; //임의의 값.
	cnt = 1;
	if (argv[1] == NULL) //단일 에코
		write(fd, "NULL\n", 5);
	else
	{
		temp = ft_strjoin("", "");
		while (argv[cnt])
		{
			write(fd, "\n", 1);
			res = ft_strjoin(temp, argv[cnt]);
			ft_putstr_fd(argv[cnt], fd);
			write(fd, "\n", 1);
			free(temp);
			temp = res;
			cnt++;	
		}
		cnt = 0;
		while (argv[cnt])
			free(argv[cnt++]);
		free(argv);
		write(fd, temp, ft_strlen(temp));
		if (option)
			write(fd, "\n", 1);
		//pipe add code
		free(temp);
	}
}

