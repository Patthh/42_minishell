/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:50:33 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:50:34 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_printf_positive_number(unsigned int n)
{
	char	digit[12];
	int		characters_written;
	int		i;

	i = 0;
	characters_written = 0;
	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	while (n > 0)
	{
		digit[i++] = (n % 10) + '0';
		n /= 10;
	}
	while (--i >= 0)
	{
		write(1, &digit[i], 1);
		characters_written++;
	}
	return (characters_written);
}

int	ft_printf_number(int n)
{
	int	character_written;

	character_written = 0;
	if (n == INT_MIN)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(1, "-", 1);
		character_written++;
		n = -n;
	}
	return (character_written + ft_printf_positive_number(n));
}
