/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:15:59 by youlee            #+#    #+#             */
/*   Updated: 2020/11/02 20:20:38 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		command_echo(char **argv, int *receiver, int *sender)
{
	//in 저장 out ->
/*	int cnt;
	int read_ret;

	cnt = 0;
	while (read_ret = read())
*/
	printf("argv[0] : %s\nargv[1] : %s\n",argv[0],argv[1]);
}
