/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:23:44 by youlee            #+#    #+#             */
/*   Updated: 2021/01/30 04:06:35 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_command(t_list **p_first_elem, int *receiver,
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
		arg_forward(p_first_elem, before, receiver, sender);
	else if (arg_type == 2)
		arg_extract(p_first_elem, before, receiver, sender);
	else if (arg_type == 3)
		arg_backward(p_first_elem, before, receiver, sender);
	else if (arg_type == 4)
		arg_semicolon(p_first_elem, current, receiver, sender);
	else if (arg_type == 5)
		arg_pipe(p_first_elem, before, receiver ,sender);
	else
	{
		execute_command(*p_first_elem, 0, receiver, sender);
		printf("exit execute_command\n");
		wait(0);
		printf("exit wait(0)\n");
	}
	return ;
}
