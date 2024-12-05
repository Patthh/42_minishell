/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_spec_d.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:43:20 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/16 14:43:05 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	ft_printf_spec_d(t_memo *memo)
{
	long	u;

	u = (long) va_arg (*memo->args, int);
	if (u < 0)
	{
		memo->plus_sign = '-';
		u = -u;
	}
	memo->base_c = HEX_LOWER;
	memo->base = 10;
	ft_printf_number (u, memo);
}
