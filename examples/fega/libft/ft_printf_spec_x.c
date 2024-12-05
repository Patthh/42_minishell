/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_spec_x.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:44:14 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/17 07:10:56 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_spec_x(const char *s, t_memo *memo)
{
	unsigned long	u;

	u = va_arg (*memo->args, unsigned int);
	memo->base_c = HEX_LOWER;
	memo->base = 16;
	memo->plus_sign = 0;
	if (*s == 'X')
		memo->base_c = HEX_UPPER;
	if (memo->prefix_o_x && u != 0)
	{
		if (*s == 'x')
			memo->prefix = HEX_LOWER_PREFIX;
		else
			memo->prefix = HEX_UPPER_PREFIX;
	}
	ft_printf_number (u, memo);
}
