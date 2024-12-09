/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/06 08:15:05 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The ft_strrchr() function is identical to strchr(), except it locates the
	last occurrence of c.
*/

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*t;
	unsigned char	u;
	unsigned char	*save;

	t = (unsigned char *) s;
	u = (unsigned char) c;
	save = NULL;
	while (*t)
	{
		if (*t == u)
			save = t;
		t++;
	}
	if (u == 0)
		save = t;
	return ((char *) save);
}
