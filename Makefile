################################################################################
## VARIABLES
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
CFLAGS			=	-Wall -Wextra -Werror -g -O0
HEADERS			=	-I$(DIR_INC) -I include -I libft/include
READLINE		=	-lreadline
RM				=	rm -rf

################################################################################
## SOURCES
SRCS			=	$(wildcard $(DIR_SRC)*.c) \
					$(wildcard $(DIR_BUILTINS)*.c) \
					$(wildcard $(DIR_LEXER)*.c) \
					$(wildcard $(DIR_PARSER)*.c) \
					$(wildcard $(DIR_SHELL)*.c) \
					$(wildcard $(DIR_SIGNALS)*.c) \
					$(wildcard $(DIR_UTILS)*.c)

OBJS			=	$(SRCS:.c=.o)
DEPS			=	$(OBJS:.o=.d)

################################################################################
## RULES
all:				$(DIR_LIBFT)$(LIBFT_NAME) $(NAME)

$(NAME):			$(OBJS)
					@echo "$(YELLOW)Linking$(NC) $(NAME)"
					@$(CC) $(CFLAGS) $(OBJS) $(DIR_LIBFT)/$(LIBFT_NAME) $(READLINE) -o $(NAME)
					@echo "$(GREEN)Build completed: $(NAME)$(NC)"

$(DIR_LIBFT)$(LIBFT_NAME):
					@echo "$(YELLOW)Building libft$(NC)"
					@$(MAKE) -C $(DIR_LIBFT) || (echo "$(RED)Error building libft$(NC)" && exit 1)

%.o: %.c
					@echo "$(YELLOW)Compiling$(NC) $<"
					@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
					@echo "$(GREEN)Compiled$(NC) $<"

clean:
					@echo "$(YELLOW)Cleaning object files$(NC)"
					@$(RM) $(OBJS) $(OBJS:.o=.d)
					@echo "$(GREEN)Clean completed$(NC)"
					@$(MAKE) -C $(DIR_LIBFT) clean

fclean:				clean
					@echo "$(YELLOW)Cleaning executable$(NC)"
					@$(RM) $(NAME)
					@echo "$(GREEN)Executable removed$(NC)"
					@$(MAKE) -C $(DIR_LIBFT) fclean

re:					fclean all

.PHONY:				all clean fclean re

################################################################################
## COLORS
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m
