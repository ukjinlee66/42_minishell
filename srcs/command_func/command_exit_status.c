/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exit_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:49:52 by youlee            #+#    #+#             */
/*   Updated: 2021/01/26 18:54:10 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// $? command process

void	command_exit_status(char **argv, int *receiver, int *sender)
{
	write(1, ret_val, ft_strlen(ret_val) + 1);
}
