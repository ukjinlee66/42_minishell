#include "minishell.h"

# define BUF_SIZE 1000

int			arg_semicolon(t_list **p_first_elem, t_list *target, int *pipe_in, int *pipe_out)
{
	t_list	*current;

	current = *p_first_elem;
	execute_command(current, target, pipe_in, pipe_out);
	pipe_in[0] = -1;
	pipe_out[0] = -1;
	current = target;
	target = target->next;
	free(current->data);
	free(current);
	handle_command(&target, pipe_in, pipe_out);
	return (0);
}
