/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sseo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 15:30:44 by sseo              #+#    #+#             */
/*   Updated: 2021/02/01 15:47:04 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	control_sender(int *sender, int new_pipe)
{
	if (sender[0] != -1)
		write(sender[0], "\0", 1);
	sender[0] = new_pipe;
	sender[1] = -1;
}

