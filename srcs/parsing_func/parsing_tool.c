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
