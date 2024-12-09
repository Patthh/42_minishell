/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/08/13 15:11:41 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The strdup() function allocates sufficient memory for a copy of the string
	s1, does the copy, and returns a pointer to it.  The pointer may subse-
	quently be used as an argument to the function free(3).
*/

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*tab;
	size_t	size;
	char	*s;

	size = ft_strlen(s1);
	tab = (char *) malloc (size + 1);
	if (!tab)
		return ((void *) 0);
	s = (char *) s1;
	while (*s)
		*tab++ = *s++;
	*tab = 0;
	return (tab - size);
}
