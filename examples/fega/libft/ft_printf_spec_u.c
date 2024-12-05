/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_spec_u.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:12:47 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/17 07:10:45 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_spec_u(t_memo *memo)
{
	unsigned long	u;

	u = (unsigned long) va_arg (*memo->args, unsigned int);
	memo->plus_sign = 0;
	memo->base = 10;
	memo->base_c = HEX_LOWER;
	ft_printf_number (u, memo);
}
