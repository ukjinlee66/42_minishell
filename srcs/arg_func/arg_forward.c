#include "minishell.h"

# define BUF_SIZE 1000

static void	arg_part(const char *file_name, int fd_in)
{
	char		buf[BUF_SIZE + 1];
	int			read_len;

	if ((read_len = read(fd_in, buf, BUF_SIZE)) >= 0)
	{
		buf[BUF_SIZE] = 0;
		write(1, file_name, ft_strlen(file_name));
		write(1, ": ", 2);
		write(1, buf, read_len);
		write(1, "\n", 1);
	}
	else
		write(1, "error!!\n", 8);
	exit(0);
}

int			arg_forward(t_list **p_first_elem, t_list *before, int *pipe_in, int *pipe_out)
{
	pid_t		pid_num;
	int			new_pipe[2];
	char		*file_name;
	int			cnt;

	cnt = 0;
	file_name = edit_list4redirection(p_first_elem, before);
	pipe(new_pipe);
	if (!(pid_num = fork()))
		arg_part(file_name, new_pipe[0]);
	else
	{
		while (pipe_out[cnt] != -1)
			cnt++;
		pipe_out[cnt] = new_pipe[1];
		pipe_out[cnt + 1] = -1;
		handle_command(p_first_elem, pipe_in, pipe_out);
	}
	return (0);
}
