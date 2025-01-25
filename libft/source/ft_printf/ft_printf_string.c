/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:50:36 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:50:37 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_printf_string(const char *str)
{
	int		characters_written;

	characters_written = 0;
	if (str == NULL)
	{
		write (1, "(null)", 6);
		characters_written = 6;
	}
	else
	{
		characters_written = write(1, str, ft_strlen(str));
	}
	return (characters_written);
}
