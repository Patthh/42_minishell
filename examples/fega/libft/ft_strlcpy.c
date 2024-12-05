/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/08/13 15:11:41 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The ft_strlcpy() copy src to dest by detsize and null terminate
	it return size of src exclude null terminate
*/
#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	size;

	len = ft_strlen (src);
	if (dstsize < 1)
		return (len);
	else if (dstsize < len + 1)
		size = dstsize - 1;
	else
		size = dstsize;
	while (size-- && *src)
		*dst++ = *src++;
	*dst = 0;
	return (len);
}
