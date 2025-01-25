/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:50:35 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:50:36 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_printf_pointer(void *ptr)
{
	int				characters_written;

	characters_written = 0;
	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		characters_written += 5;
	}
	else
	{
		write(1, "0x", 2);
		characters_written += 2;
		characters_written += ft_printf_hex((unsigned long)ptr, 'x');
	}
	return (characters_written);
}
