/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
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

char	*ft_strtrim(const char *s, const char *set)
{
	size_t	f_index;
	size_t	l_index;
	char	*tab;

	tab = NULL;
	if (s == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s));
	if (!*s)
		return ((char *) ft_calloc(1, 1));
	f_index = 0;
	l_index = ft_strlen(s) - 1;
	while (f_index < l_index && ft_strchr(set, s[f_index]))
		f_index++ ;
	while (f_index < l_index && ft_strchr(set, s[l_index]))
		l_index-- ;
	if (f_index <= l_index && !ft_strchr(set, s[f_index]))
		tab = ft_substr(s, f_index, l_index - f_index + 1);
	else
		tab = ft_calloc (1, 1);
	return (tab);
}
