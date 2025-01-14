################################################################################
## ARGUMENTS
MAKEFLAGS += --no-print-directory

NAME		= libft.a
HEADERS		= libft.h

################################################################################
## DIRECTORIES

INC_DIR		= ./include/
SRC_DIR		= ./source/

################################################################################
## COMPILATION & FLAGS
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pedantic -g -O0
AR 			= ar rcs
RM			= rm -f

################################################################################
## SOURCES

DIR_IS		=	$(SRC_DIR)ft_is/ft_isalnum.c \
				$(SRC_DIR)ft_is/ft_isalpha.c \
				$(SRC_DIR)ft_is/ft_isascii.c \
				$(SRC_DIR)ft_is/ft_isblank.c \
				$(SRC_DIR)ft_is/ft_iscntrl.c \
				$(SRC_DIR)ft_is/ft_isdigit.c \
				$(SRC_DIR)ft_is/ft_isgraph.c \
				$(SRC_DIR)ft_is/ft_islower.c \
				$(SRC_DIR)ft_is/ft_isprint.c \
				$(SRC_DIR)ft_is/ft_ispunct.c \
				$(SRC_DIR)ft_is/ft_isspace.c \
				$(SRC_DIR)ft_is/ft_isupper.c \
				$(SRC_DIR)ft_is/ft_isxdigit.c

DIR_LST		=	$(SRC_DIR)ft_lst/ft_lstadd_back.c \
				$(SRC_DIR)ft_lst/ft_lstadd_front.c \
				$(SRC_DIR)ft_lst/ft_lstclear.c \
				$(SRC_DIR)ft_lst/ft_lstdelone.c \
				$(SRC_DIR)ft_lst/ft_lstforeach.c \
				$(SRC_DIR)ft_lst/ft_lstiter.c \
				$(SRC_DIR)ft_lst/ft_lstlast.c \
				$(SRC_DIR)ft_lst/ft_lstmap.c \
				$(SRC_DIR)ft_lst/ft_lstnew.c \
				$(SRC_DIR)ft_lst/ft_lstsize.c

DIR_MEM		=	$(SRC_DIR)ft_mem/ft_bzero.c \
				$(SRC_DIR)ft_mem/ft_calloc.c \
				$(SRC_DIR)ft_mem/ft_memchr.c \
				$(SRC_DIR)ft_mem/ft_memcmp.c \
				$(SRC_DIR)ft_mem/ft_memcpy.c \
				$(SRC_DIR)ft_mem/ft_memmove.c \
				$(SRC_DIR)ft_mem/ft_memset.c

DIR_PUT		=	$(SRC_DIR)ft_put/ft_putchar_fd.c \
				$(SRC_DIR)ft_put/ft_putendl_fd.c \
				$(SRC_DIR)ft_put/ft_putnbr_fd.c \
				$(SRC_DIR)ft_put/ft_putstr_fd.c

DIR_STR		=	$(SRC_DIR)ft_str/ft_split.c \
				$(SRC_DIR)ft_str/ft_strchr.c \
				$(SRC_DIR)ft_str/ft_strcmp.c \
				$(SRC_DIR)ft_str/ft_strcspn.c \
				$(SRC_DIR)ft_str/ft_strdup.c \
				$(SRC_DIR)ft_str/ft_striteri.c \
				$(SRC_DIR)ft_str/ft_strjoin_char.c \
				$(SRC_DIR)ft_str/ft_strjoin.c \
				$(SRC_DIR)ft_str/ft_strlcat.c \
				$(SRC_DIR)ft_str/ft_strlcpy.c \
				$(SRC_DIR)ft_str/ft_strlen.c \
				$(SRC_DIR)ft_str/ft_strmapi.c \
				$(SRC_DIR)ft_str/ft_strncmp.c \
				$(SRC_DIR)ft_str/ft_strndup.c \
				$(SRC_DIR)ft_str/ft_strnstr.c \
				$(SRC_DIR)ft_str/ft_strpbrk.c \
				$(SRC_DIR)ft_str/ft_strrchr.c \
				$(SRC_DIR)ft_str/ft_strrev.c \
				$(SRC_DIR)ft_str/ft_strspn.c \
				$(SRC_DIR)ft_str/ft_strstr.c \
				$(SRC_DIR)ft_str/ft_strtok.c \
				$(SRC_DIR)ft_str/ft_strtol.c \
				$(SRC_DIR)ft_str/ft_strtrim.c \
				$(SRC_DIR)ft_str/ft_substr.c

DIR_TO		=	$(SRC_DIR)ft_to/ft_atoi_base.c \
				$(SRC_DIR)ft_to/ft_atoi.c \
				$(SRC_DIR)ft_to/ft_itoa.c \
				$(SRC_DIR)ft_to/ft_tolower.c \
				$(SRC_DIR)ft_to/ft_toupper.c

# DIR_PF		=	$(SRC_DIR)ft_printf/ft_printf_character.c \
# 				$(SRC_DIR)ft_printf/ft_printf_hex.c \
# 				$(SRC_DIR)ft_printf/ft_printf_number.c \
# 				$(SRC_DIR)ft_printf/ft_printf_pointer.c \
# 				$(SRC_DIR)ft_printf/ft_printf_string.c \
# 				$(SRC_DIR)ft_printf/ft_printf_unsigned_number.c \
# 				$(SRC_DIR)ft_printf/ft_printf.c \
# 				$(SRC_DIR)ft_printf/ft_utoa.c

SRCS 		= $(DIR_IS) $(DIR_LST) $(DIR_MEM) $(DIR_PUT) $(DIR_STR) $(DIR_TO) 
# $(DIR_PF)
OBJS		= $(SRCS:.c=.o)

################################################################################
## RULES

################################################################################
## RULES

all:				$(NAME)

$(NAME):			$(OBJS)
					@$(AR) $(NAME) $(OBJS)
					
%.o: %.c
					@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@
					
clean:
					@$(RM) $(OBJS)
					
fclean:				clean
					@$(RM) $(NAME)
					
re:					fclean all

.PHONY: 			all clean fclean re

################################################################################
## COLORS
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m
