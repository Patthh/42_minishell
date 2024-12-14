/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artclave <artclave@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 22:55:34 by ugolin-olle       #+#    #+#             */
/*   Updated: 2024/03/13 20:21:23 by artclave         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s);
void	*ft_memmove(void *dst, const void *src, size_t len);

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*res;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!(res))
		return (NULL);
	ft_memmove(res, s1, i);
	res[i] = '\0';
	return (res);
}
