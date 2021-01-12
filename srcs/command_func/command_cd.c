/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 19:57:26 by youlee            #+#    #+#             */
/*   Updated: 2021/01/12 15:54:39 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	command_cd(char **argv, int *receiver, int *sender)
{
	getcwd(cur_path, PATH_SIZE); //current path
	chdir(argv[1]);
	getcwd(cur_path, PATH_SIZE); //current path
}
