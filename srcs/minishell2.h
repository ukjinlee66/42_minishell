#ifndef MINISHELL_H
#define MINISHELL_H

/*
**===========================header files================================
*/

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

/*
**===========================define values===============================
*/
#define PATH_SIZE 1024

/*
**============================structure==================================
*/

/*
**===========================source files================================
*/

/*
**		main.c
*/

void	main_process(void);
int		get_next_line(char **line);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);

#endif
