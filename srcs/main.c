#include "minishell.h"

void		main_process(void)
{
	t_list			*inputs;
	char			*line;
	int				gnl_ret;

	if ((gnl_ret = get_next_line(&line)) == -1)
	{
		exit (2);			//unexpected case
	}
	if (gnl_ret == 0)
		builtin_exit();
	inputs = split_line((const char *)line);
	free(line);
	line = 0;

	//temp: for test
	t_list			*test;
	char			*test_str;

	test = inputs;
	while (test)
	{
		test_str = (char *)test->data;
		printf("test for pasing: %s -> %d\n", test_str, ft_strlen(test_str));
		test = test->next;
	}
	free_list(inputs);
}

int			main(void)
{
	char			path[PATH_SIZE];

	while (1)
	{
		getcwd(path, PATH_SIZE);
		write(1, path, ft_strlen(path));
		write(1, "$ ", 2);
		main_process();
	}
	return (0);
}
