#include "minishell.h"

# define BUF_SIZE 1000

static char	**construct_argv(t_list *list_start, t_list *list_end)
{
	int			cnt;
	t_list		*temp;
	char		**new_argv;

	cnt = 0;
	temp = list_start;
	while (temp != list_end)
	{
		temp = temp->next;
		cnt++;
	}
	if (!(new_argv = (char **)malloc(sizeof(char *) * (cnt + 1))))
		return (0);		//malloc fail
	cnt = 0;
	while (list_start != list_end)
	{
		temp = list_start;
		list_start = list_start->next;
		new_argv[cnt] = (char *)temp->data;
		free(temp);
		cnt++;
	}
	new_argv[cnt] = 0;
	return (new_argv);
}

int			execute_command(t_list *list_start, t_list *list_end, \
								int *pipe_in, int *pipe_out)
{
	char		**argv;
	//pid_t		pid_num;
	int cnt;
	char		buf[1000];

	argv = construct_argv(list_start, list_end);
	/*
	if (!(pid_num = fork()))//child
	{
		if (!ft_strcmp(argv[0], "echo"))
			command_echo(argv);
		else if (!ft_strcmp(argv[0], "cd"))
			command_cd(argv);
		else if (!ft_strcmp(argv[0], "pwd"))
			command_pwd(argv);
		else if (!ft_strcmp(argv[0], "export"))
			command_export(argv);
		else if (!ft_strcmp(argv[0], "unset"))
			command_unset(argv);
		else if (!ft_strcmp(argv[0], "env"))
			command_env(argv);
		else if (!ft_strcmp(argv[0], "exit"))
			command_exit(argv);
		else if (argv[0][0] == '.' && argv[0][1] =='/')
			command_relative_run(argv);
		else
			launch_excutable(argv); //error case
		pipe	
	
	}
	else//parent
	{
		cnt = 0;
		while (pipe_in[cnt])
			read(pipe_in[cnt++],buf,BUFFER_SIZE);

	}
	*/

	int			cnt;
	int			read_len;
	char		buf[BUF_SIZE + 1];

	cnt = 0;
	write(1, "command: ", 9);
	while (argv[cnt])
	{
		write(1, argv[cnt], ft_strlen((const char *)argv[cnt]));
		write(1, " ", 1);
		cnt++;
	}
	write(1, "\n", 1);

	cnt = 0;
	while (argv[cnt])
	{
		free(argv[cnt]);
		cnt++;
	}
	free(argv);

	cnt = 0;
	while (pipe_in[cnt] != -1)
	{
		read_len = read(pipe_in[cnt], buf, BUF_SIZE);
		buf[read_len] = 0;
		write(1, "test input: ", 12);
		write(1, buf, read_len);
		write(1, "\n", 1);
		cnt++;
	}

	cnt = 0;
	while (pipe_out[cnt] != -1)
	{
		write(pipe_out[cnt], "test output", 11);
		cnt++;
	}
	return (0);
}
