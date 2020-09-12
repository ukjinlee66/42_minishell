NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror

INCLUDES = -I includes/

LIBS = -lft -L ./srcs/Libft/

SRCS = srcs/main.c					\
	   srcs/get_interactive_line.c	\
	   srcs/list_func.c				\
	   srcs/split_line.c			\
	   srcs/func/command_exit.c

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFALGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@cd srcs/Libft; make
	$(CC) $(CFLAGS) $(LIBS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	@cd srcs/Libft; make fclean
	@rm -f $(OBJS)
	@echo "clean up!!"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
