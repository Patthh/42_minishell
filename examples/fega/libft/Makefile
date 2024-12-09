#/****************************************************************************/
#/*                                                                          */
#/*                                                        :::      :::::::: */
#/*   makefile libft.a                                   :+:      :+:    :+: */
#/*                                                    +:+ +:+         +:+   */
#/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+      */
#/*                                                +#+#+#+#+#+   +#+         */
#/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#           */
#/*   Updated: 2023/08/13 15:11:41 by pnamnil          ###   ########.fr     */
#/*                                                                          */
#/****************************************************************************/

NAME = libft.a

INCLUDE = includes

NC="\\033[0m"
BOLD="\\033[1m"
ULINE="\\033[4m"
RED="\\033[31m"
GREEN="\\033[32m"
YELLOW="\\033[33m"
BLUE="\\033[34m"
MAGENTA="\\033[35m"

CC = cc
CFLEGS = -Wall -Werror -Wextra -I$(INCLUDE)

# Rule to compile a .c source file into a .o object file
bin/%.o: %.c
	@mkdir -p bin
	@$(CC) $(CFLEGS) -c $< -o $@

SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c
SRCS += ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c 
SRCS += ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c
SRCS += ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c
SRCS += ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c
SRCS += ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c
SRCS += ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
OBJS = $(patsubst %.c, bin/%.o, $(SRCS))

B_SRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c
B_SRCS += ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c
B_SRCS += ft_lstmap.c
B_OBJS = $(patsubst %.c, bin/%.o, $(B_SRCS))

FT_PRINTF_PREFIX = ft_printf
FT_PRINTF_SRCS = $(addprefix $(FT_PRINTF_PREFIX), .c _flags.c _utils.c\
				_spec_c.c _spec_s.c _spec_d.c _spec_p.c _spec_u.c _spec_x.c)
FT_PRINTF_OBJS = $(patsubst %.c, bin/%.o, $(FT_PRINTF_SRCS))

GET_NEXT_LINE_SRCS = get_next_line.c get_next_line_utils.c
GET_NEXT_LINE_OBJS = $(patsubst %.c, bin/%.o, $(GET_NEXT_LINE_SRCS))

all: $(NAME)

$(NAME): $(OBJS) $(B_OBJS) $(FT_PRINTF_OBJS) $(GET_NEXT_LINE_OBJS)
	@ar rcs $(NAME) $(OBJS) $(B_OBJS) $(FT_PRINTF_OBJS) $(GET_NEXT_LINE_OBJS)
	@echo "${GREEN}libft.a is compiled${NC}"

bonus: all

clean:
	@rm -rf bin
	@echo "${GREEN}libft.a is cleaned${NC}"

fclean: clean
	@rm -f $(NAME)
	@echo "${GREEN}libft.a is fcleaned${NC}"

re: fclean all

.PHONY: all clean fclean re bonus
