#include "minishell.h"

static void	arg_part(int *pipe_fd, int fd)
{
	char		buf[IO_BUF_SIZE + 1];
	int			read_len;

	close(pipe_fd[1]);
	g_pid_stat = false;
	if ((read_len = read(pipe_fd[0], buf, IO_BUF_SIZE)) > 0)
	{
		buf[read_len - 1] = '\n';
		write(fd, buf, read_len);
	}
	else if (read_len < 0)
		write(1, "unexpected error!!\n", 19);
	close(fd);
	close(pipe_fd[0]);
	exit(0);
}

void		arg_forward(t_list **p_first_elem, t_list *before, int *receiver, int *sender)
{
	int			fd;
	int			eno;
	pid_t		pid_num;
	int			new_pipe[2];
	char		*file_name;

	file_name = edit_list4redirection(p_first_elem, before);
	if ((fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0664)) < 0)
	{
		eno = errno;
		control_open_error(file_name, eno, *p_first_elem);
		control_sender(sender, -1);
		if ((file_name = ft_itoa(eno)))
			ft_strlcpy(g_ret_str, file_name, ft_strlen(file_name) + 1);
		free(file_name);
	}
	else
	{
		free(file_name);
		pipe(new_pipe);
		if (!(pid_num = fork()))
			arg_part(new_pipe, fd);
		else
		{
			close(fd);
			close(new_pipe[0]);
			g_pid_stat = true;
			control_sender(sender, new_pipe[1]);
			handle_command(p_first_elem, receiver, sender);
		}
	}
}
