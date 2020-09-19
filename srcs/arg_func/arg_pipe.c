#include "minishell.h"

int			arg_pipe(t_list **p_first_elem, t_list *before, int *pipe_in, int *pipe_out)
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
		pipe_in[0] = new_pipe[0];
		pipe_in[1] = -1;
		pipe_out[0] = -1;
		handle_command(&current, pipe_in, pipe_out);
	}
	else
	{
		free_list(current);
		while (pipe_out[cnt] != -1)
			cnt++;
		pipe_out[cnt] = new_pipe[1];
		pipe_out[cnt + 1] = -1;
		handle_command(p_first_elem, pipe_in, pipe_out);
	}
	return (0);
}
