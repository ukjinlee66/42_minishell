/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:15:59 by youlee            #+#    #+#             */
/*   Updated: 2020/11/02 21:41:14 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		command_echo(char **argv, int *receiver, int *sender)
{
	int cnt;
	char *res;
	char *temp;
	int len;

	len = 0;
	cnt = 1;
	//in 저장 out ->
/*	int cnt;
	int read_ret;

	cnt = 0;
	while (read_ret = read())
*/
	if (argv[1] == NULL) //단일 에코
		write(1, "NULL\n", 5);
	else
	{
		temp = ft_strjoin("", "");
		while (argv[cnt])
		{
			write(1, "\n", 1);
			res = ft_strjoin(temp, argv[cnt]);
			ft_putstr_fd(argv[cnt], 1);
			write(1, "\n", 1);
			free(temp);
			temp = res;
			cnt++;	
		}
		cnt = 0;
		while (argv[cnt])
			free(argv[cnt++]);
		free(argv);
		write(1, temp, ft_strlen(temp));
		//pipe add code
		free(temp);
	}
}

