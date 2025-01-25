/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned_number.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:50:37 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:50:39 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_printf_unsigned_number(unsigned int n)
{
	char			*str;
	int				characters_written;

	str = ft_utoa(n);
	characters_written = 0;
	if (str != NULL)
	{
		characters_written = write(1, str, ft_strlen(str));
		free (str);
	}
	return (characters_written);
}
