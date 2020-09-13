/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:23:44 by youlee            #+#    #+#             */
/*   Updated: 2020/09/13 20:41:34 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_command(t_list *command_lines)
{
	t_list		*current;

	while (command_lines)
	{
		current = command_lines;
		if (current->data == "")
	}
}
