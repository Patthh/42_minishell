################################################################################
## VARIABLES
MAKEFLAGS += --no-print-directory

NAME            =   minishell
LIBFT_NAME      =   libft.a

################################################################################
## DIRECTORIES
DIR_INC         =   ./include/
DIR_SRC         =   ./source/
DIR_LIBFT       =   ./libft/

DIR_BUILTINS    =   $(DIR_SRC)builtins/
DIR_LEXER       =   $(DIR_SRC)lexer/
DIR_PARSER      =   $(DIR_SRC)parser/
DIR_SHELL       =   $(DIR_SRC)shell/
DIR_SIGNALS     =   $(DIR_SRC)signals/
DIR_UTILS       =   $(DIR_SRC)utils/

INCLUDE         =   -I include -I libft/include

################################################################################
## COMPILATION & FLAGS
CC              =   cc
CFLAGS          =   -Wall -Wextra -Werror -g -O0 #-fsanitize=address
HEADERS         =   -I$(DIR_INC) -I include -I libft/include
READLINE        =   -lreadline
RM              =   rm -rf

################################################################################
## SOURCES
SRCS            =   $(wildcard $(DIR_SRC)*.c) \
					$(wildcard $(DIR_BUILTINS)*.c) \
					$(wildcard $(DIR_LEXER)*.c) \
					$(wildcard $(DIR_PARSER)*.c) \
					$(wildcard $(DIR_SHELL)*.c) \
					$(wildcard $(DIR_SIGNALS)*.c) \
					$(wildcard $(DIR_UTILS)*.c)

OBJS            =   $(SRCS:.c=.o)
DEPS            =   $(OBJS:.o=.d)

TOTAL_FILES     =   $(words $(SRCS))
COMPILED_FILES  =   0
DOTS            =   $(shell printf ".%.0s" $(shell seq $(TOTAL_FILES)))

################################################################################
## RULES
all:                $(DIR_LIBFT)$(LIBFT_NAME) $(NAME)
					@echo -e "$(GREEN)Build complete! $(NAME) has been created.$(NC)"

$(NAME):            $(OBJS)
					@$(CC) $(CFLAGS) $(OBJS) $(DIR_LIBFT)/$(LIBFT_NAME) $(READLINE) -o $(NAME)
					
$(DIR_LIBFT)$(LIBFT_NAME):
					@$(MAKE) -C $(DIR_LIBFT) || (echo "$(RED)Error building libft$(NC)" && exit 1)

%.o: %.c
					@$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES) + 1))))
					@DOTS_LEFT=$(shell echo "$(DOTS)" | cut -c$(COMPILED_FILES)-) ; \
					printf "\r$(CYAN)Compiling: [$(COMPILED_FILES)/$(TOTAL_FILES)] 🟡%s$(NC)" "$${DOTS_LEFT}"
					@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
					@if [ $(COMPILED_FILES) -eq $(TOTAL_FILES) ]; then echo; fi
					
clean:
					@$(RM) $(OBJS) $(OBJS:.o=.d)
					@$(MAKE) -C $(DIR_LIBFT) clean

fclean:             clean
					@$(RM) $(NAME)
					@$(MAKE) -C $(DIR_LIBFT) fclean

re:                 fclean all

.PHONY:             all clean fclean re

################################################################################
## COLORS
GREEN = \033[0;32m
CYAN = \033[0;36m
RED = \033[0;31m
NC = \033[0m
