#ifndef MINISHELL_H
# define MINISHELL_H

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
# define PATH_SIZE 1024

/*
**============================structure==================================
*/
typedef struct		s_list
{
	void			*data;
	struct s_list	*next;

}					t_list;


/*
**===========================source files================================
*/

/*
**		main.c
*/
void		main_process(void);

/*
**		get_interactive_line.c
*/
int			get_interactive_line(char **line);

/*
**		builtin_exit.c
*/
void		builtin_exit(void);

/*
**		list_func.c
*/
int			add_data(t_list **p_list, void **p_data);
void		free_list(t_list *list);

/*
**		split_line.c
*/
t_list		*split_line(const char *line);

/*
**		Libft
*/
void		ft_bzero(void *src, size_t n);
size_t		ft_strlen(const char *src);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);

#endif
