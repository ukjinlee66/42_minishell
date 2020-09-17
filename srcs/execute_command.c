#include "minishell.h"

int			execute_commands(t_list *list) //error->non-zero
{
	if (current->data == "echo")
		command_echo() // (echo) (" ")
	else if (current->data == "cd")
		command_cd()
	else if (current->data == "pwd")
		command_pwd()
	else if (current->data == "export")
		command_export()
	else if (current->data == "unset")
		command_unset()
	else if (current->data == "env")
		command_env()
	else if (current->data == "exit")
		command_exit()
}
