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
# include <stdbool.h>

/*
**===========================define values===============================
*/
# define PATH_SIZE 1024
# define PIPE_BUF_SIZE 1000
# define IO_BUF_SIZE 1024

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
**		args
*/
int			arg_backward(t_list **p_first_elem, t_list *before, int *pipe_in, int *pipe_out);
int			arg_extract(t_list **p_first_elem, t_list *before, int *pipe_in, int *pipe_out);
int			arg_forward(t_list **p_first_elem, t_list *before, int *pipe_in, int *pipe_out);
int			arg_semicolon(t_list **p_first_elem, t_list *target, int *pipe_in, int *pipe_out);
int			arg_pipe(t_list **p_first_elem, t_list *before, int *pipe_in, int *pipe_out);

/*
**		commands
*/
void		handle_command(t_list **p_first_elem, int *pipe_in, int *pipe_out);
int			execute_command(t_list *list_start, t_list *list_end, int *pipe_in, int *pipe_out);
void		command_exit(void);


/*
**		command functions
*/
void		command_echo(char **argv, int *receiver, int *sender);
void		command_cd(char **argv, int *receiver, int *sender);
void		command_env(char **argv, int *receiver, int *sender);
void		command_exit(void);
void		command_pwd(char **argv, int *receiver, int *sender);
void		command_unset(char **argv, int *receiver, int *sender);
void		command_export(char **argv, int *receiver, int *sender);
void		command_relative_run(char **argv, int *receiver, int *sender);
void		launch_excutable(char **argv, int *receiver, int *sender);

/*
**		list_func.c
*/
int			add_data(t_list **p_list, void **p_data);
void		free_list(t_list *list);
void		*edit_list4redirection(t_list **p_first_elem, t_list *before);

/*
**		parsing_tool.c
*/
int			get_arg_type(const char *arg);

/*
**		split_line.c
*/
t_list		*split_line(const char *line);

/*
**		get_interactive_line.c
*/
int			get_interactive_line(char **line);

/*
**		Libft
*/
void		ft_bzero(void *src, size_t n);
size_t		ft_strlen(const char *src);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strcmp(const char *src1, const char *src2);
void		ft_putstr_fd(char *s, int fd);

/*
**		util
*/

void	two_pointer_free(char ***argv);
char	*uppercase_conversion(char *str);
void	copy_env_list(char **envp);
void	copy_env_list2(char envl[2048][2048],
		char envp[2048][2048]);
void	envl_sort(void);
int		get_env_list(char *chr);

/*
**		variable
*/

char	cur_path[PATH_SIZE];
char	envl[2048][2048]; //2048 x 2048 env array
char	soenvl[2048][2048]; //sort env array
#endif
