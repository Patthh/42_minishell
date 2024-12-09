/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/12/27 11:29:41 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The atoi() function converts the initial 
	portion of the string pointed to by str
	to int representation.
	if overflow unsinged long return 0 or -1
*/

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long	n;
	int				sign;

	n = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++ ;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++ ;
	}
	while (*str >= '0' && *str <= '9')
	{
		if ((n >= SIZE_MAX / 10) || (n >= SIZE_MAX / 10 - (*str - '0')))
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		n = (n * 10) + (*str - '0');
		str++ ;
	}
	return (n * sign);
}
