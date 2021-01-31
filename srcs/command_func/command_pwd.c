/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 19:57:51 by youlee            #+#    #+#             */
/*   Updated: 2021/01/31 23:42:42 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_pwd(char **argv, int *receiver, int *sender)
{
	char buf[PATH_SIZE];

	getcwd(buf, PATH_SIZE);
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	return (0);
}
