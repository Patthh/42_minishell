/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 08:10:05 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/17 17:00:46 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* protect if write false, it set memo->nb = -1 */
t_bool	ft_printf_putc(char c, t_memo *memo)
{
	int	write_result;

	write_result = write(memo->fd, &c, 1);
	if (write_result == -1)
	{
		memo->cnt = -1;
		return (FALSE);
	}
	memo->cnt += write_result;
	return (TRUE);
}

/* 
**	special case with 0 flag it put sign or prefix before pad 0
**	do not increase len becouse it increase in ft_print_number_h1
*/
static char	*ft_printf_number_h3(char *p, t_memo *memo)
{
	int	i;

	if (memo->plus_sign != 0)
	{
		if (!ft_printf_putc(*p++, memo))
			return (NULL);
		memo->plus_sign = 0;
	}
	else if (memo->prefix)
	{
		i = 0;
		while (memo->prefix[i++])
		{
			if (!ft_printf_putc (*p++, memo))
				return (NULL);
		}
	}
	return (p);
}

/* write charecter */
static void	ft_printf_number_h2(char *n, char *p, int len, t_memo *memo)
{
	if (len < memo->n_pad && !memo->l_just)
	{
		if (memo->padc == '0')
		{
			p = ft_printf_number_h3 (p, memo);
			if (p == NULL)
				return ;
		}
		while (len < memo->n_pad)
		{
			if (!ft_printf_putc (memo->padc, memo))
				return ;
			len++;
		}
	}
	while (p < n)
	{
		if (!ft_printf_putc (*p++, memo))
			return ;
	}
	while (len++ < memo->n_pad && memo->l_just)
	{
		if (!ft_printf_putc (memo->padc, memo))
			return ;
	}
}

/* handle sign and prefix */
static void	ft_printf_number_h1(char *n, char *p, int len, t_memo *memo)
{
	int	i;

	if (memo->plus_sign)
	{
		*--p = memo->plus_sign;
		len++ ;
	}
	if (memo->prefix)
	{
		i = ft_strlen(memo->prefix);
		while (i > 0)
		{
			*--p = memo->prefix[--i];
			len++ ;
		}
	}
	ft_printf_number_h2(n, p, len, memo);
}

/*
**	make string from number with base
**	and make O for precition
*/
void	ft_printf_number(unsigned long u, t_memo *memo)
{
	char	n[MAX_BUF + 1];
	char	*p;
	int		len;

	n[MAX_BUF] = 0;
	p = &n[MAX_BUF - 1];
	if (u == 0 && memo->n_pre == 0)
		p++ ;
	while (u / memo->base)
	{
		*p-- = memo->base_c[u % memo->base];
		u /= memo->base;
	}
	*p = memo->base_c[u % memo->base];
	len = &n[MAX_BUF] - p;
	while (len < memo->n_pre)
	{
		len++ ;
		*--p = '0';
	}
	ft_printf_number_h1 (&n[MAX_BUF], p, len, memo);
}
