#include "minishell.h"

# define BUF_SIZE 1000

static void	arg_part(const char *file_name, int fd_out)
{
	char		buf[BUF_SIZE + 1];
	int			write_len;

	strcpy(buf, file_name);
	if ((write_len = write(fd_out, buf, ft_strlen((const char *)buf))) < 0)
		write(1, "error!!\n", 8);
	exit(0);
}

int			arg_backward(t_list **p_first_elem, t_list *before, int *pipe_in, int *pipe_out)
{
	pid_t		pid_num;
	int			new_pipe[2];
	char		*file_name;
	int			cnt;

	cnt = 0;
	file_name = edit_list4redirection(p_first_elem, before);
	pipe(new_pipe);
	if (!(pid_num = fork()))
		arg_part(file_name, new_pipe[1]);
	else
	{
		while (pipe_in[cnt] != -1)
			cnt++;
		pipe_in[cnt] = new_pipe[0];
		pipe_in[cnt + 1] = -1;
		handle_command(p_first_elem, pipe_in, pipe_out);
	}
	return (0);
}
