/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:50:40 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:50:41 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_utoa(unsigned int n)
{
	int				length;
	unsigned int	temp;
	char			*str;

	length = 1;
	temp = n;
	while (temp >= 10)
	{
		temp /= 10;
		length++;
	}
	str = (char *)malloc(length + 1);
	if (str == NULL)
		return (NULL);
	str[length] = '\0';
	while (length > 0)
	{
		str[--length] = '0' + (n % 10);
		n /= 10;
	}
	return (str);
}
