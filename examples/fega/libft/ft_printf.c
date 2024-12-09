/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 10:13:49 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/17 16:09:38 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

/* this function use for test flags */
/*
void	test_flags(t_memo *memo)
{
	printf ("memo->fd: %d\n", memo->fd);
	printf ("memo->cnt: %d\n", memo->cnt);
	printf ("memo->prefix: %s\n", memo->prefix);
	printf ("memo->padc: '%c'\n", memo->padc);
	printf ("memo->plus_sign: '%c'\n", memo->plus_sign);
	printf ("memo->l_just: %u\n", memo->l_just);
	printf ("memo->prefix_o_x: %u\n", memo->prefix_o_x);
	printf ("memo->n_pad: %d\n", memo->n_pad);
	printf ("memo->n_pre: %d\n", memo->n_pre);
}
*/

static char	*ft_printf_spec(const char *s, t_memo *memo)
{
	if (*s == '%' || *s == 'c')
		ft_printf_spec_c (s, memo);
	else if (*s == 's')
		ft_printf_spec_s (memo);
	else if (*s == 'd' || *s == 'i')
		ft_printf_spec_d (memo);
	else if (*s == 'p')
		ft_printf_spec_p (memo);
	else if (*s == 'u')
		ft_printf_spec_u (memo);
	else if (*s == 'x' || *s == 'X')
		ft_printf_spec_x (s, memo);
	else
		memo->cnt = -1;
	return ((char *)++s);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	t_memo	memo;

	ft_printf_init_memo (&args, &memo);
	va_start (*memo.args, s);
	while (*s && memo.cnt != -1)
	{
		if (*s != '%')
		{
			ft_printf_putc (*s++, &memo);
			continue ;
		}
		s++ ;
		s = ft_printf_getsign (s, &memo);
		s = ft_printf_getflags (s, &memo);
		s = ft_printf_spec (s, &memo);
		ft_printf_reset_memo(&memo);
	}
	va_end(*memo.args);
	return (memo.cnt);
}
