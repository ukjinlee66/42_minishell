/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:30:26 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 18:30:27 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		arg_pipe(t_list **p_first_elem, t_list *before, int *receiver, int *sender)
{
	t_list		*current;
	pid_t		pid_num;
	int			new_pipe[2];

	current = before->next;
	before->next = 0;
	before = current;
	current = current->next;
	free(before->data);
	free(before);
	pipe(new_pipe);
	if (!(pid_num = fork()))
	{
		close(new_pipe[1]);
		g_pid_stat = false;
		free_list(*p_first_elem);
		receiver[0] = new_pipe[0];
		receiver[1] = -1;
		sender[0] = -1;
		handle_command(&current, receiver, sender);
		exit(0); //not end program
	}
	else
	{
		close(new_pipe[0]);
		g_pid_stat = true;
		free_list(current);
		if (sender[0] != -1)
			write(new_pipe[1], "\0", 1);
		else
			sender[0] = new_pipe[1];
		sender[1] = -1;
		handle_command(p_first_elem, receiver, sender);
	}
}
