NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I includes/

LIBS = -lft -L ./srcs/Libft/

SRCS = srcs/main.c							\
	   srcs/arg_func/arg_backward.c			\
	   srcs/arg_func/arg_extract.c			\
	   srcs/arg_func/arg_forward.c			\
	   srcs/arg_func/arg_pipe.c				\
	   srcs/arg_func/arg_semicolon.c		\
	   srcs/arg_func/arg_func.c				\
	   srcs/command_func/command_exit.c		\
	   srcs/command_func/execute_command.c	\
	   srcs/command_func/handle_command.c	\
	   srcs/command_func/command_cd.c		\
	   srcs/command_func/command_echo.c		\
	   srcs/command_func/command_env.c		\
	   srcs/command_func/command_export.c		\
	   srcs/command_func/command_pwd.c		\
	   srcs/command_func/command_relative_run.c		\
	   srcs/command_func/command_unset.c		\
	   srcs/command_func/launch_excutable.c		\
	   srcs/command_func/command_absolute_run.c \
	   srcs/parsing_func/list_func.c		\
	   srcs/parsing_func/split_line.c		\
	   srcs/parsing_func/parsing_tool.c		\
	   srcs/parsing_func/parsing_tool2.c		\
	   srcs/read_write_func/get_interactive_line.c	\
	   srcs/util/two_free_func.c  \
	   srcs/util/uppercase_conversion.c \
	   srcs/util/envlist_util.c \
	   srcs/util/envlist_util2.c \
	   srcs/util/envlist_util3.c \
	   srcs/util/handle_sig.c \
	   srcs/util/handle_path.c

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFALGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@cd srcs/Libft; make bonus
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

all: $(NAME)

clean:
	@cd srcs/Libft; make fclean
	@rm -f $(OBJS)
	@echo "clean up!!"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
