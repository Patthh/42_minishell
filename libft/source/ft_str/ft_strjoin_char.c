/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:51:01 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:51:02 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strjoin_char(const char *str, char c)
{
	char	*result;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	ft_memcpy(result, str, len);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}
