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

void	handle_command(t_list **p_first_elem, int *pipe_in, int *pipe_out)
{
	t_list		*before;
	t_list		*current;
	int			arg_type;

	before = 0;
	current = *p_first_elem;
	arg_type = 0;
	while (current)
	{
		if ((arg_type = get_arg_type((const char *)current->data)))
			break ;
		before = current;
		current = current->next;
	}
	if (arg_type == 1)
		arg_forward(p_first_elem, before, pipe_in, pipe_out);
	else if (arg_type == 2)
		arg_extract(p_first_elem, before, pipe_in, pipe_out);
	else if (arg_type == 3)
		arg_backward(p_first_elem, before, pipe_in, pipe_out);
	else if (arg_type == 4)
		arg_semicolon(p_first_elem, current, pipe_in, pipe_out);
	else if (arg_type == 5)
		arg_pipe(p_first_elem, before, pipe_in ,pipe_out);
	else
	{
		execute_command(*p_first_elem, 0, pipe_in, pipe_out);
		wait(0);
		exit(0);
	}
}
