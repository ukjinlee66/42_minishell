#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

extern char **environ;

int		main(int argc, char *argv[])
{
	char **new_argv;
	char command[] = "ls";

	new_argv = (char **)malloc(sizeof(char) * (argc + 1));
	new_argv[0] = command;

	for (int i = 1; i < argc; i++)
	{
		new_argv[i] = argv[i];
	}
	new_argv[argc] = 0;
	printf("%s\n", new_argv[0]);
	printf("%s\n", new_argv[1]);
	execve("/bin/ls", new_argv, environ);
	return (0);
}
