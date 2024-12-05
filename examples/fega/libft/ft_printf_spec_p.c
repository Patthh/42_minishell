/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_spec_p.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:07:21 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/17 07:10:20 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_printf_spec_p(t_memo *memo)
{
	unsigned long	u;

	u = va_arg (*memo->args, unsigned long);
	memo->prefix = HEX_LOWER_PREFIX;
	memo->base = 16;
	memo->base_c = HEX_LOWER;
	memo->plus_sign = 0;
	ft_printf_number(u, memo);
}
