NAME = minishell

#SRC_DIR = src
# SRC_FILES = main.c
SRC = src/execute.c src/find_cmd.c src/get_next_line.c src/builtins.c src/export.c src/unset.c \
		src/parse_envp.c src/build_envp.c src/free_memory.c src/main.c src/parse_cmd.c \
		src/parse_cmd_utils.c src/exit_utils.c src/redirections.c src/execute_utils.c \
		src/execute_pipes.c src/envp.c src/cd.c src/echo.c src/pwd.c src/env.c src/exit.c \
		src/parse_list.c src/merge_and_replace.c src/debug.c src/list_utils.c src/link_list.c \
		src/free_list.c src/parse_tree.c src/parse_tree_redirect.c src/parse_tree_utils.c \
		src/heredoc.c src/pain.c src/torture.c src/hell.c
# execute_utils.c 
OBJ = $(SRC:.c=.o)
HEADER = src/minishell.h

CC = cc
CFLAGS = -Wall -Wextra -Werror -O0 -g
RM = rm -rf

MYLIB_DIR = libft
MYLIB = $(MYLIB_DIR)/libft.a

all: $(NAME)

%.o: %.c $(HEADER) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(MYLIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(MYLIB) -lreadline

$(MYLIB):
	@make -C $(MYLIB_DIR)

clean:
	$(RM) $(OBJ)
	@make clean -C $(MYLIB_DIR)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(MYLIB_DIR)

re: fclean all

.PHONY: all clean fclean re
