/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youlee <youlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 13:02:53 by youlee            #+#    #+#             */
/*   Updated: 2021/02/02 19:48:20 by youlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
**					args
*/
void				arg_backward(t_list **p_first_elem, t_list *before,
		int *pipe_in, int *pipe_out);
void				arg_extract(t_list **p_first_elem, t_list *before,
		int *pipe_in, int *pipe_out);
void				arg_forward(t_list **p_first_elem, t_list *before,
		int *pipe_in, int *pipe_out);
void				arg_semicolon(t_list **p_first_elem, t_list *target,
		int *pipe_in, int *pipe_out);
void				arg_pipe(t_list **p_first_elem, t_list *before,
		int *pipe_in, int *pipe_out);
void				control_sender(int *sender, int new_pipe);
void				control_open_error(int eno, t_list *first_elem);
/*
**					commands
*/
void				handle_command(t_list **p_first_elem,
		int *pipe_in, int *pipe_out);
int					execute_command(t_list *list_start, t_list *list_end,
		int *pipe_in, int *pipe_out);
int					command_exit(char **argv);
/*
**		command functions
*/
int					command_echo(char **argv, int *receiver, int *sender,
		bool option_val);
int					command_cd(char **argv, int *receiver, int *sender);
int					cd_home(void);
int					command_env(char **argv, int *receiver, int *sender);
int					command_pwd(char **argv, int *receiver, int *sender);
int					command_unset(char **argv, int *receiver, int *sender);
void				clear_soenvl(void);
int					command_export(char **argv, int *receiver, int *sender);
int					command_relative_run(char **argv, int *receiver,
		int *sender);
char				*make_com(char *argv);
char				**make_envp(void);
int					launch_excutable(char **argv, int *receiver,
		int *sender);
int					command_absolute_run(char **argv, int *receiver,
		int *sender);
/*
**					list_func.c
*/
int					add_data(t_list **p_list, void **p_data);
void				free_list(t_list *list);
void				*edit_list4redirection(t_list **p_first_elem,
		t_list *before);
/*
**					parsing_tool.c
*/
int					get_arg_type(const char *arg);
int					update_data(const char *line, char **p_data,
		size_t *p_start, size_t *p_len);
int					flush_data(t_list **p_out, const char *line,
		char **p_data, size_t *p_start);
t_list				*print_parse_error(t_list *out, char *data,
		int eno, t_list *temp);
int					parse_env_variables(const char *line, char **p_data,
		size_t *p_start);
/*
**					parsing_tool2.c
*/
int					parse_double_quote_loop(const char *line, char **p_data,
		size_t *p_start, size_t *p_len);
/*
**					split_line.c
*/
t_list				*split_line(const char *line);
/*
**					get_interactive_line.c
*/
int					get_interactive_line(char **line);
/*
**					Libft
*/
void				ft_bzero(void *src, size_t n);
size_t				ft_strlen(const char *src);
char				*ft_substr(char const *s, unsigned int start,
		size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
int					ft_strcmp(const char *src1, const char *src2);
void				ft_putstr_fd(char *s, int fd);
size_t				ft_strlcpy(char *dest, const char *src, size_t n);
char				*ft_strdup(const char *src);
char				**ft_split(const char *s, char c);
char				*ft_strchr(const char *src, int c);
void				*ft_memset(void *src, int c, size_t n);
char				*ft_itoa(int n);
int					ft_atoi(const char *nptr);
/*
**					util
*/
void				two_pointer_free(char ***argv);
char				*uppercase_conversion(char *str);
void				copy_env_list(char **envp);
void				copy_env_list2(char envl[2048][2048],
char				envp[2048][2048]);
void				envl_sort(void);
int					get_env_list(char *chr);
void				add_str_de(void);
void				copy_arr(char *a, char*b, int num);
bool				check_env(char *find, char *b);
void				set_env_list(char *name, char *value);
void				add_double(char (*env)[2048]);
int					get_soenv_list(char *chr);
void				set_env_list2(char *name, char *value);
void				handle_sig(int sig_num);
void				handle_sig2(int sig_num);
int					put_err(int errn);
int					dir_err(char **path, char **argv, char **envp);
int					is_dir(char **argv);
int					stat_check(int status);
/*
**					variable
*/
char				g_cur_path[PATH_SIZE];
char				g_envl[2048][2048];
char				g_soenvl[2048][2048];
char				g_print_buf[2048];
DIR					*g_dp;
char				g_ret_str[10];
bool				g_pid_stat;
#endif
