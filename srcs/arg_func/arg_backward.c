#include "minishell.h"

static void	arg_part(int fd_out, int fd)
{
	char		buf[IO_BUF_SIZE + 1];
	int			write_len;

	if ((write_len = read(fd, buf, IO_BUF_SIZE)) < 0)
		write(1, "unexpected error!!\n", 19);
	else
	{
		buf[write_len] = 0;
		write(fd_out, buf, write_len);
	}
	close(fd);
	close(fd_out);
	exit(0);
}

void		arg_backward(t_list **p_first_elem, t_list *before, int *receiver, int *sender)
{
	int			fd;
	pid_t		pid_num;
	int			new_pipe[2];
	char		*file_name;

	file_name = edit_list4redirection(p_first_elem, before);
	if ((fd = open(file_name, O_RDONLY, 0664)) < 0)
	{
		control_open_error(file_name, errno, *p_first_elem);
		control_sender(sender, -1);
	}
	else
	{
		free(file_name);
		pipe(new_pipe);
		if (!(pid_num = fork()))
			arg_part(new_pipe[1], fd);
		else
		{
			close(fd);
			receiver[0] = new_pipe[0];
			receiver[1] = -1;
			handle_command(p_first_elem, receiver, sender);
		}
	}
}
