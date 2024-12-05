/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnamnil <pnamnil@student.42bangkok.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 14:40:50 by pnamnil           #+#    #+#             */
/*   Updated: 2023/08/13 15:11:41 by pnamnil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Allocates (with malloc(3)) and returns a substring
	from the string ’s’.
	The substring begins at index ’start’ and is of
	maximum size ’len’.
*/

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*tab;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
	{
		start = s_len;
		len = 0;
	}
	else if (s_len - start <= len)
		len = s_len - start;
	tab = (char *) malloc (len + 1);
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, &s[start], len + 1);
	return (tab);
}

/*
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*tab;
	char	*str;
	size_t	i;
	size_t	j;
	size_t	s_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	tab = (char *) malloc (len + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (s[i] && i < start)
		i++ ;
	j = 0;
	while (s[i] && j < len)
		tab[j++] = s[i++];
	tab[j] = 0;
	str = ft_strdup(tab);
	free (tab);
	return (str);
}
*/
