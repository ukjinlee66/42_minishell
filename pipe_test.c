#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int		main(void)
{
	int		fd1[2];
	int		fd2[2];
	char	buf[100];
	pid_t	pid_num;
	char	*test_start = "test start";
	char	*test_done = "test done";
	char	out[100];

	pipe(fd1);
	pipe(fd2);
	if (!(pid_num = fork()))
	{
		read(fd1[0], buf, 100);
		sprintf(out, "i'm a child process: %s\n", buf);
		write(1, out, strlen(out));

		dup2(fd2[1], 1);
		close(fd2[1]);
		write(1, test_done, strlen(test_done));
	}
	else
	{
		write(fd1[1], test_start, 11);
		wait(NULL);

		read(fd2[0], buf, 100);
		sprintf(out, "i'm a parent process: %s\n", buf);
		write(1, out, strlen(out));
	}
	return (0);
}
