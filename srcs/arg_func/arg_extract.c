#include "minishell.h"

static int		arg_part(int fd_in, int fd)
{
	char		buf[IO_BUF_SIZE + 1];
	int			read_len;

	if ((read_len = read(fd_in, buf, sizeof(buf))) >= 0)
	{
		buf[read_len] = 0;
		printf("test: %d\n", read_len);
		write(fd, buf, read_len);
	}
	else
		write(1, "unexpected error!!\n", 19);
	close(fd_in);
	close(fd);
	return (0);
}

int				arg_extract(t_list **p_first_elem, t_list *before, int *receiver, int *sender)
{
	int			fd;
	pid_t		pid_num;
	int			statloc;
	int			new_pipe[2];
	char		*file_name;
	char		*str;

	file_name = edit_list4redirection(p_first_elem, before);
	if ((fd = open(file_name, O_RDWR | O_CREAT | O_APPEND)) < 0)
	{
		free(file_name);
		str = strerror(errno);
		write(1, str, ft_strlen(str));
		return (1);
	}
	write(fd, "test\n", 5);
	free(file_name);
	pipe(new_pipe);
	if (!(pid_num = fork()))
		return (arg_part(new_pipe[0], fd));
	else
	{
		close(fd);
		if (sender[0] != -1)
		{
			write(sender[0], "\0", 1);
		}
		sender[0] = new_pipe[1];
		sender[1] = -1;
		return (handle_command(p_first_elem, receiver, sender));
	}
}
