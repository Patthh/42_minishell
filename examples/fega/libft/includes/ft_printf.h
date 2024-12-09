/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:46:17 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/17 16:53:21 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"

# define HEX_UPPER "0123456789ABCDEF"
# define HEX_LOWER "0123456789abcdef"
# define HEX_UPPER_PREFIX "0X"
# define HEX_LOWER_PREFIX "0x"
# define FLAGS "-.*0123456789"
# define TRUE 1
# define FALSE 0
# define MAX_BUF 1000

typedef unsigned char	t_bool;
typedef struct s_memo
{
	int		cnt;
	int		fd;
	char	plus_sign;
	char	*prefix;
	char	padc;
	char	*base_c;
	t_bool	l_just;
	t_bool	prefix_o_x;
	int		n_pad;
	int		n_pre;
	int		base;
	va_list	*args;
}	t_memo;

int		ft_printf(const char *s, ...);

// flags
char	*ft_printf_getsign(const char *s, t_memo *memo);
char	*ft_printf_getflags(const char *s, t_memo *memo);
void	ft_printf_init_memo(va_list *args, t_memo *memo);
void	ft_printf_reset_memo(t_memo *memo);

// spec
void	ft_printf_spec_c(const char *s, t_memo *memo);
void	ft_printf_spec_s(t_memo *memo);
void	ft_printf_spec_d(t_memo *memo);
void	ft_printf_spec_p(t_memo *memo);
void	ft_printf_spec_u(t_memo *memo);
void	ft_printf_spec_x(const char *s, t_memo *memo);

// utils
t_bool	ft_printf_putc(char c, t_memo *memo);
void	ft_printf_number(unsigned long u, t_memo *memo);

#endif
