/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_backward.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 18:29:53 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 19:38:48 by sseo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	arg_part(int *pipe_fd, int fd)
{
	char		buf[IO_BUF_SIZE + 1];
	int			write_len;

	close(pipe_fd[0]);
	g_pid_stat = false;
	if ((write_len = read(fd, buf, IO_BUF_SIZE)) < 0)
		write(1, "unexpected error!!\n", 19);
	else
	{
		buf[write_len] = 0;
		write(pipe_fd[1], buf, write_len);
	}
	close(fd);
	close(pipe_fd[1]);
	exit(0);
}

static int	check_open(t_list **p_first_elem, t_list *before, int *sender)
{
	int			fd;
	char		*file_name;
	char		*str_err;

	file_name = edit_list4redirection(p_first_elem, before);
	if ((fd = open(file_name, O_RDONLY, 0664)) < 0)
	{
		control_open_error(errno, *p_first_elem);
		control_sender(sender, -1);
		if ((str_err = ft_itoa(1)))
		{
			write(1, str_err, ft_strlen(str_err));
			ft_strlcpy(g_ret_str, str_err, ft_strlen(str_err) + 1);
			free(str_err);
		}
	}
	free(file_name);
	return (fd);
}

void		arg_backward(t_list **p_first_elem, t_list *before,
		int *receiver, int *sender)
{
	int			fd;
	pid_t		pid_num;
	int			new_pipe[2];

	if ((fd = check_open(p_first_elem, before, sender)) >= 0)
	{
		pipe(new_pipe);
		if (!(pid_num = fork()))
			arg_part(new_pipe, fd);
		else
		{
			close(fd);
			close(new_pipe[1]);
			g_pid_stat = true;
			if (receiver[0])
				close(receiver[0]);
			receiver[0] = new_pipe[0];
			receiver[1] = -1;
			handle_command(p_first_elem, receiver, sender);
		}
	}
}
