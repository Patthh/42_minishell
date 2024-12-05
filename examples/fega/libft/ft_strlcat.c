/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/08/13 15:11:41 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	ft_strlcat() appends string src to the end of dst.  It will append at most
	dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate, unless
	dstsize is 0 or the original dst string was longer than dstsize (in
	practice this should not happen as it means that either dstsize is
	incorrect or that dst is not a proper string).
*/

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	c;
	size_t	d;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (!(dst) && dstsize == 0)
		return (src_len);
	if (dstsize <= ft_strlen(dst))
		return (dstsize + src_len);
	c = ft_strlen(dst);
	d = 0;
	while (src[d] && c + 1 < dstsize)
		dst[c++] = src[d++];
	dst[c] = '\0';
	return (ft_strlen(dst) + ft_strlen(&src[d]));
}
