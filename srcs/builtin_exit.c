#include "minishell.h"

void		builtin_exit(void)
{
	write(1, "exit\n", 5);
	exit (1);
}
