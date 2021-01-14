#include "minishell.h"

int			arg_pipe(t_list **p_first_elem, t_list *before, int *receiver, int *sender)
{
	t_list		*current;
	pid_t		pid_num;
	int			new_pipe[2];
	int			cnt;

	cnt = 0;
	current = before->next;
	before->next = 0;
	before = current;
	current = current->next;
	free(before->data);
	free(before);
	pipe(new_pipe);
	if (!(pid_num = fork()))
	{
		free_list(*p_first_elem);
		receiver[0] = new_pipe[0];
		receiver[1] = -1;
		sender[0] = -1;
		handle_command(&current, receiver, sender);
		exit(0);
	}
	else
	{
		free_list(current);
		while (sender[cnt] != -1)
			cnt++;
		sender[cnt] = new_pipe[1];
		sender[cnt + 1] = -1;
		handle_command(p_first_elem, receiver, sender);
	}
	return (0);
}
