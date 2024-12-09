/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/06 08:18:54 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The ft_strchr() function locates the first occurrence of c (converted to a
	char) in the string pointed to by s.  The terminating null character is
	considered to be part of the string; therefore if c is ‘\0’, the
	functions locate the terminating ‘\0’.
*/

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*t;
	unsigned char	u;

	t = (unsigned char *) s;
	u = (unsigned char) c;
	while (*t)
	{
		if (*t == u)
			return ((char *) t);
		t++ ;
	}
	if (u == 0)
		return ((char *) t);
	return (NULL);
}
