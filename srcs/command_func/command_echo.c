/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:15:59 by youlee            #+#    #+#             */
/*   Updated: 2021/01/30 03:30:51 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			command_echo(char **argv, int *receiver, int *sender)
{
	int cnt;
	char *res;
	char *temp;
	int fd;
	bool option_val;

	int i = 0;
	//if (receiver[0] != -1) //test code
	//{
	//	read(receiver[0], print_buf, 1000);
//		printf("i am receive %s\n",print_buf);
	//}
	option_val = false;
//	if (sender[0] == -1)
//		fd = 1;
//	else
//		fd = 125; //임의의 값.
	cnt = 1;
	if (argv[1] == NULL) //단일 에코
		write(1, "\n", 5);
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
			ft_putstr_fd(argv[cnt], 1);
			if (sender[0] != -1)
			{
				ft_strlcpy(print_buf, argv[cnt], ft_strlen(argv[cnt]) + 1);
				write(1, print_buf, ft_strlen(print_buf) + 1);
			}
			if (argv[cnt + 1] != NULL)
				write(1, " ", 1);
			//free(temp);
			temp = res;
			cnt++;
		}
		cnt = 0;
		//clean function two pointer
		//two_pointer_free(&argv);
		if (option_val == false)
			write(1, "\n", 1);
		//pipe add code
		free(temp);
		//exit(0);
	}
	return (0);
}

void		command_echo2(char **argv, int *receiver, int *sender)
{
	//33 line -> 25줄 빼오기
}
