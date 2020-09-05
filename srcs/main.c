#include "minishell2.h"

void		main_process(void)
{
	char		*line;
	int			gnl_ret;

	if ((gnl_ret = get_next_line(&line)) == -1)
	{
		exit (1);
	}
	if (gnl_ret == 0)
		exit (1);
	printf("%s\n", line);
}

int			main(void)
{
	char		path[PATH_SIZE];

	while (1)
	{
		getcwd(path, PATH_SIZE);
		write(1, path, ft_strlen(path));
		write(1, "$ ", 2);
		main_process();
	}
	return (0);
}
