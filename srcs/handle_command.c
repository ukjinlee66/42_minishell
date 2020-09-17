/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/12 16:23:44 by youlee            #+#    #+#             */
/*   Updated: 2020/09/14 18:37:47 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_arg_type(const char *arg)
{
	if (ft_strcmp(arg, ">") == 0)
		return (1);
	else if (ft_strcmp(arg, ">>") == 0)
		return (2);
	else if (ft_strcmp(arg, "<") == 0)
		return (3);
	else if (ft_strcmp(arg, ";") == 0)
		return (4);
	else if (ft_strcmp(arg, "|") == 0)
		return (5);
	else
		return (0);
}

void	handle_command(t_list *target, int *pipe_in, int *pipe_out)
{
	t_list		*before;
	t_list		*current;
	t_list		*after;
	int			arg_type;
	const char	*data;
	pid_t		pid_num;
	int			fd1[2];
	int			fd2[2];
	char		buf[1000];
	int			read_len;
	int			cnt;

	before = 0;
	current = target;
	arg_type = 0;
	cnt = 0;

	if (!current)
		exit(0);
	while (current)
	{
		data = (const char *)current->data;
		if ((arg_type = get_arg_type(data)))
			break ;
		before = current;
		current = current->next;
	}
	if (arg_type == 1)
	{
		pipe(fd1);
		pipe(fd2);
		if (!(pid_num = fork()))
		{
			read_len = read(fd1[0], buf, 1000);
			write(1, "forward redirection: ", 22);
			write(1, buf, read_len);
			write(1, "\n", 1);
			free_list(target);
			exit(0);
		}
		else
		{
			after = current->next;
			before->next = after->next;
			free(current->data);
			free(current);
			free(after->data);
			free(after);
			while (pipe_out[cnt] != -1)
				cnt++;
			pipe_out[cnt] = dup(fd1[1]);
			pipe_out[cnt + 1] = -1;
			handle_command(target, pipe_in, pipe_out);
		}
	}
	else if (arg_type == 2)
	{
		pipe(fd1);
		pipe(fd2);
		if (!(pid_num = fork()))
		{
			read_len = read(fd1[0], buf, 1000);
			write(1, "extract redirection: ", 22);
			write(1, buf, read_len);
			write(1, "\n", 1);
			exit(0);
		}
		else
		{
			after = current->next;
			before->next = after->next;
			free(current->data);
			free(current);
			free(after->data);
			free(after);
			while (pipe_out[cnt] != -1)
				cnt++;
			pipe_out[cnt] = fd1[1];
			pipe_out[cnt + 1] = -1;
			handle_command(target, pipe_in, pipe_out);
		}
	}
	else if (arg_type == 3)
	{
		pipe(fd1);
		pipe(fd2);
		if (!(pid_num = fork()))
		{
			write(fd2[1], "backward input\n", 16);
			exit(0);
		}
		else
		{
			after = current->next;
			before->next = after->next;
			free(current->data);
			free(current);
			free(after->data);
			free(after);
			while (pipe_in[cnt] != -1)
				cnt++;
			pipe_in[cnt] = fd2[0];
			pipe_in[cnt + 1] = -1;

			handle_command(target, pipe_in, pipe_out);
		}
	}
	else if (arg_type == 4)
	{
		while (pipe_in[cnt] != -1)
		{
			read_len = read(pipe_in[cnt], buf, 1000);
			write(1, buf, read_len);
			write(1, "\n", 1);
			cnt++;
		}

		write(1, "sample command!\n", 16);
		while (target != current)
		{
			data = target->data;
			write(1, data, ft_strlen(data));
			write(1, "\n", 1);
			before = target;
			target = target->next;
			free((void *)data);
			free(before);
		}

		cnt = 0;
		while (pipe_out[cnt] != -1)
		{
			write(pipe_out[cnt], "sample input", 13);
			cnt++;
		}

		before = target;
		target = target->next;
		free(before->data);
		free(before);
		pipe_in[0] = -1;
		pipe_out[0] = -1;
		handle_command(target, pipe_in, pipe_out);
	}
	else if (arg_type == 5)
	{
		pipe(fd1);
		pipe(fd2);
		after = current->next;
		free(current->data);
		free(current);
		before->next = 0;
		if (!(pid_num = fork()))
		{
			free_list(target);
			int		new_pipe_in[1000];
			int		new_pipe_out[1000];

			new_pipe_in[0] = fd2[0];
			new_pipe_in[1] = -1;
			new_pipe_out[0] = -1;
			handle_command(after, new_pipe_in, new_pipe_out);
			exit(0);
		}
		else
		{
			free_list(after);
			while (pipe_out[cnt] != -1)
				cnt++;
			pipe_out[cnt] = fd2[1];
			pipe_out[cnt + 1] = -1;

			handle_command(target, pipe_in, pipe_out);
		}
	}
	else
	{
		while (pipe_in[cnt] != -1)
		{
			read_len = read(pipe_in[cnt], buf, 1000);
			write(1, buf, read_len);
			write(1, "\n", 1);
			cnt++;
		}
		cnt = 0;
		while (pipe_out[cnt] != -1)
		{
			write(pipe_out[cnt], "hello", 5);
			cnt++;
		}

		while (target)
		{
			data = (const char *)target->data;
			write(1, data, ft_strlen(data));
			write(1, "\n", 1);
			before = target;
			target = target->next;
			free((void *)data);
			free(before);
		}
		wait(0);
		exit(0);
	}
}

/*
void	handle_command(t_list *command_lines, int *fd_pipe)
{
	char		buf[1000];
	t_list		*before;
	t_list		*current;
	const char	*line;

	current = command_lines;
	line = (const char *)command_lines->data;
	if (ft_strcmp(line, ">") == 0 || ft_strcmp(line, ">>") == 0 || ft_strcmp(line, "|"))
	{
		//wait signal from parent pid and do their job
	}
	else if (ft_strcmp(line, "<") == 0)
	{
		//open target and send
	}
	while (current)
	{
		line = (const char *)current->data;
		if (ft_strcmp(line, ">") == 0 || ft_strcmp(line, ">>") == 0 || \
			ft_strcmp(line, "<") == 0 || ft_strcmp(line, ";") == 0 || \
			ft_strcmp(line, "|") == 0)
		{
			//fork!
		}
	}
}
*/
