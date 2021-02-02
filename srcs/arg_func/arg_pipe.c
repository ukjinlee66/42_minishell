/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:30:26 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 20:17:17 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent(t_list **p_first_elem, int *receiver, int *sender, \
		int pipe_out)
{
	g_pid_stat = true;
	if (sender[0] != -1)
		close(pipe_out);
	else
		sender[0] = pipe_out;
	sender[1] = -1;
	handle_command(p_first_elem, receiver, sender);
}

static void	child(t_list **p_first_elem, int *receiver, int *sender, \
		int pipe_in)
{
	g_pid_stat = false;
	if (receiver[0] != -1)
		close(receiver[0]);
	if (sender[0] != -1)
		close(sender[0]);
	receiver[0] = pipe_in;
	receiver[1] = -1;
	sender[0] = -1;
	handle_command(p_first_elem, receiver, sender);
	exit(0);
}

void		arg_pipe(t_list **p_first_elem, t_list *before, \
		int *receiver, int *sender)
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
		free_list(*p_first_elem);
		child(&current, receiver, sender, new_pipe[0]);
	}
	else
	{
		close(new_pipe[0]);
		free_list(current);
		parent(p_first_elem, receiver, sender, new_pipe[1]);
	}
}
