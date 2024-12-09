/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/08/13 15:11:41 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The ft_strnstr() function locates the first occurrence of the null-terminated
	string needle in the null-terminated string haystack.
*/

#include <stdlib.h>
#include "libft.h"

/* use slidding windows and ft_strncmp() */

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;
	char	*s;

	if (haystack == NULL && len == 0)
		return (NULL);
	needle_len = ft_strlen (needle);
	s = (char *) haystack;
	if (needle_len == 0)
		return (s);
	i = 0;
	while (s[i] && i + needle_len - 1 < len)
	{
		if (ft_strncmp(&s[i], needle, needle_len) == 0)
			return (&s[i]);
		i++ ;
	}
	return (NULL);
}
