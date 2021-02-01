/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:23:44 by youlee            #+#    #+#             */
/*   Updated: 2021/02/01 14:19:35 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		handle_command(t_list **p_first_elem, int *receiver,
		int *sender)
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
		return (arg_forward(p_first_elem, before, receiver, sender));
	else if (arg_type == 2)
		return (arg_extract(p_first_elem, before, receiver, sender));
	else if (arg_type == 3)
		return (arg_backward(p_first_elem, before, receiver, sender));
	else if (arg_type == 4)
		return (arg_semicolon(p_first_elem, current, receiver, sender));
	else if (arg_type == 5)
		return (arg_pipe(p_first_elem, before, receiver ,sender));
	else
	{
		execute_command(*p_first_elem, 0, receiver, sender);
		wait(0);
		return (1);
	}
}
