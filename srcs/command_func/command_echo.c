/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:15:59 by youlee            #+#    #+#             */
/*   Updated: 2020/11/02 21:02:31 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		command_echo(char **argv, int *receiver, int *sender)
{
	int argv1_len;

	argv1_len = 0;
	//in 저장 out ->
/*	int cnt;
	int read_ret;

	cnt = 0;
	while (read_ret = read())
*/
	printf("argv[0] : %s\nargv[1] : %s\n",argv[0],argv[1]);
	if (argv[1] == NULL) //단일 에코
		write(1, "\n", 1);
	while (argv[1][argv1_len])
		argv1_len++;
	if (argv[1][0] == '"' && )
}
