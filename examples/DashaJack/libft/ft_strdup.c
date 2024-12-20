/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 09:59:15 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/02 14:25:33 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	s = (char *)malloc(len + 1 * sizeof(char));
	if (s == 0)
		return (0);
	ft_strlcpy(s, s1, len + 1);
	return (s);
}
