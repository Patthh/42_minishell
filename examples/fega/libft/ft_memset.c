/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/09/06 07:55:36 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The ft_memset() function writes len bytes of value c (converted to an
     unsigned char) to the string b.
*/
#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*s;
	unsigned char	u;

	s = (unsigned char *) b;
	u = (unsigned) c;
	while (len--)
		*s++ = u;
	return (b);
}
