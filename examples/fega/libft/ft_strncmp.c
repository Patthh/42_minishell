/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/06 08:09:07 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The ft_strncmp() function compares not more than n characters.  Because
	strncmp() is designed for comparing strings rather than binary data,
	characters that appear after a ‘\0’ character are not compared.
*/

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *) s1;
	b = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (*a && *a == *b && --n)
	{
		a++ ;
		b++ ;
	}
	return (*a - *b);
}
