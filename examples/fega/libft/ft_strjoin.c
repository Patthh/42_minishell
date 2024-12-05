/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/08/13 15:11:41 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Allocates (with malloc(3)) and returns a new
	string, which is the result of the concatenation
	of ’s1’ and ’s2’.
*/

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*tab;
	char	*t;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	if (s1 != NULL && s2 == NULL)
		return (ft_strdup(s1));
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	s1_len = ft_strlen (s1);
	s2_len = ft_strlen (s2);
	tab = (char *) malloc (s1_len + s2_len + 1);
	if (!tab)
		return (NULL);
	t = (char *) s1;
	while (*t)
		*tab++ = *t++;
	t = (char *) s2;
	while (*t)
		*tab++ = *t++;
	*tab = 0;
	return (tab - s1_len - s2_len);
}
