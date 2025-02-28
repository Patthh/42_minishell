################################################################################
## VARIABLES
MAKEFLAGS += --no-print-directory

NAME			=	minishell
LIBFT_NAME		=	libft.a

################################################################################
## DIRECTORIES
DIR_INC			=	./include/
DIR_SRC			=	./source/
DIR_LIBFT		=	./libft/

DIR_BUILTINS	=	$(DIR_SRC)builtins/
DIR_LEXER		=	$(DIR_SRC)lexer/
DIR_PARSER		=	$(DIR_SRC)parser/
DIR_SHELL		=	$(DIR_SRC)shell/
DIR_SIGNALS		=	$(DIR_SRC)signals/
DIR_UTILS		=	$(DIR_SRC)utils/

INCLUDE			=	-I include -I libft/include

################################################################################
## COMPILATION & FLAGS
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -g -O0 #-fsanitize=address
HEADERS			=	-I$(DIR_INC) -I include -I libft/include
READLINE		=	-lreadline
RM				=	rm -rf

################################################################################
## SOURCES
SRCS = \
        $(DIR_SRC)/main.c \
        $(DIR_BUILTINS)/ft_cd.c \
        $(DIR_BUILTINS)/ft_echo.c \
        $(DIR_BUILTINS)/ft_env.c \
        $(DIR_BUILTINS)/ft_exit.c \
        $(DIR_BUILTINS)/ft_export.c \
        $(DIR_BUILTINS)/ft_pwd.c \
        $(DIR_BUILTINS)/ft_unset.c \
        $(DIR_LEXER)/token_bonus.c \
        $(DIR_LEXER)/token_utils.c \
        $(DIR_LEXER)/token_utils2.c \
        $(DIR_LEXER)/token_utils3.c \
        $(DIR_LEXER)/token_utils4.c \
        $(DIR_LEXER)/token_utils5.c \
        $(DIR_LEXER)/token_wildcard.c \
        $(DIR_LEXER)/tokenizer.c \
        $(DIR_PARSER)/parser.c \
        $(DIR_PARSER)/parser_bonus.c \
        $(DIR_PARSER)/parser_heredoc.c \
        $(DIR_PARSER)/parser_utils.c \
        $(DIR_PARSER)/parser_utils2.c \
        $(DIR_PARSER)/parser_utils3.c \
        $(DIR_PARSER)/parser_utils4.c \
        $(DIR_PARSER)/parser_utils5.c \
        $(DIR_PARSER)/setup_heredoc.c \
        $(DIR_SHELL)/exec_redir.c \
        $(DIR_SHELL)/execute_pipe.c \
        $(DIR_SHELL)/execute_status.c \
        $(DIR_SHELL)/executor.c \
        $(DIR_SHELL)/pathfinder.c \
        $(DIR_SHELL)/setup_pipe.c \
        $(DIR_SHELL)/shell.c \
        $(DIR_SHELL)/validator.c \
        $(DIR_SHELL)/validator2.c \
        $(DIR_SIGNALS)/signals.c \
        $(DIR_UTILS)/utils.c \
        $(DIR_UTILS)/utils_cd.c \
        $(DIR_UTILS)/utils_error.c \
        $(DIR_UTILS)/utils_error2.c \
        $(DIR_UTILS)/utils_error3.c \
        $(DIR_UTILS)/utils_error4.c \
        $(DIR_UTILS)/utils_export.c \
        $(DIR_UTILS)/utils_export2.c \
        $(DIR_UTILS)/utils_export3.c \
        $(DIR_UTILS)/utils_free.c \
        $(DIR_UTILS)/utils_free2.c \
        $(DIR_UTILS)/utils_shell.c

OBJS			=	$(SRCS:.c=.o)
DEPS			=	$(OBJS:.o=.d)

TOTAL_FILES		=	$(words $(SRCS))
COMPILED_FILES	=	0
DOTS			=	$(shell printf ".%.0s" $(shell seq $(TOTAL_FILES)))

################################################################################
## RULES
all:				$(DIR_LIBFT)$(LIBFT_NAME) $(NAME)
					@echo "$(GREEN)Build complete! $(NAME) has been created.$(NC)"

$(NAME):			$(OBJS)
					@$(CC) $(CFLAGS) $(OBJS) $(DIR_LIBFT)/$(LIBFT_NAME) $(READLINE) -o $(NAME)

$(DIR_LIBFT)$(LIBFT_NAME):
					@$(MAKE) -C $(DIR_LIBFT) || (echo "$(RED)Error building libft$(NC)" && exit 1)

%.o: %.c
					@$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES) + 1))))
					@DOTS_LEFT=$(shell echo "$(DOTS)" | cut -c$(COMPILED_FILES)-) ; \
					printf "\33[2K\r$(CYAN)Currently compiling: $< $(COMPILED_FILES)/$(TOTAL_FILES)$(NC) 🟡%s"
					@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
					@if [ $(COMPILED_FILES) -eq $(TOTAL_FILES) ]; then echo; fi

clean:
					@echo "$(YELLOW)Cleaning object files...$(NC)"
					@$(RM) $(OBJS) $(OBJS:.o=.d)
					@$(MAKE) -C $(DIR_LIBFT) clean
					@echo "\r$(GREEN)Object files cleaned!$(NC)"

fclean:				clean
					@echo "$(YELLOW)Cleaning minishell executable...$(NC)"
					@$(RM) $(NAME)
					@$(MAKE) -C $(DIR_LIBFT) fclean
					@echo "\r$(GREEN)Executable cleaned!$(NC)"

re:					fclean all

.PHONY:				all clean fclean re

################################################################################
## COLORS
GREEN = \033[0;32m
CYAN = \033[0;36m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m
