/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:23:44 by youlee            #+#    #+#             */
/*   Updated: 2020/09/14 18:37:47 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void command_line_sum(t_list *command_lines)
{
	
}

void	handle_command(t_list *command_lines)
{
	t_list		*current;

	while (command_lines)
	{
		//|, <> 의 경우 인자로 같이넘겨준다.
		//무조건 함수의 인자는 2개의형태의 void * 형이며 구분자의 형태에따라 응용가능.
		current = command_lines;
		
		if (current->data == "echo")
			command_echo() // (echo) (" ")
		else if (current->data == "cd")
			command_cd()
		else if (current->data == "pwd")
			command_pwd()
		else if (current->data == "export")
			command_export()
		else if (current->data == "unset")
			command_unset()
		else if (current->data == "env")
			command_env()
		else if (current->data == "exit")
			command_exit()
	}
}
