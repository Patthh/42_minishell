/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_spec_s.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 09:37:27 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/17 16:22:52 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_printf_str_h1(char *s, t_memo *memo)
{
	int	n;

	n = 0;
	while (*s)
	{
		if (n >= memo->n_pre && memo->n_pre >= 0)
			break ;
		if (!ft_printf_putc (*s++, memo))
			return ;
		n++ ;
	}
	if (memo->n_pad > 0 && memo->l_just)
	{
		while (n++ < memo->n_pad)
		{
			if (!ft_printf_putc (32, memo))
				return ;
		}
	}
}

static void	ft_printf_str(char *s, t_memo *memo)
{
	char	*p;
	int		n;

	if (memo->n_pad > 0 && !memo->l_just)
	{
		n = 0;
		p = s;
		if (memo->n_pre < 0)
			memo->n_pre = INT_MAX;
		while (*p++ && n < memo->n_pre)
			n++ ;
		while (n++ < memo->n_pad)
		{
			if (!ft_printf_putc (32, memo))
				return ;
		}
	}
	ft_printf_str_h1 (s, memo);
}

void	ft_printf_spec_s(t_memo *memo)
{
	char	*s;

	s = va_arg (*memo->args, char *);
	if (s == NULL)
		s = "(null)";
	ft_printf_str (s, memo);
}
