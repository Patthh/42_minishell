/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/08/13 15:11:41 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 The ft_memmove() function copies len bytes from string src to string dst.
 The two strings may overlap; the copy is always 
	done in a non-destructive manner.
*/
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*d;
	char	*s;

	if (dst == src)
		return (dst);
	i = -1;
	d = (char *) dst;
	s = (char *) src;
	if (d > s)
		while (n --)
			d[n] = s[n];
	else
		while (++i < n)
			d[i] = s[i];
	return (dst);
}
