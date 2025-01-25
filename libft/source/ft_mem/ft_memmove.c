/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:50:27 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:50:28 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

// moves memory safely for overlapping areas
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*first;
	char	*last;
	size_t	i;

	first = (char *)src;
	last = (char *)dst;
	i = 0;
	if (!dst && !src)
		return (NULL);
	if (last > first)
	{
		while (n-- > 0)
		{
			last[n] = first[n];
		}
	}
	else
	{
		while (i < n)
		{
			last[i] = first[i];
			i++;
		}
	}
	return (dst);
}

// int main(void)
// {
// 	char	string[50] = "Hello, Tony!";
// 	char	ft_string[50] = "Hello, Tony!";

// 	printf("Before: %s (std)\n", string);
// 	memmove(string + 7, string, 6);
// 	printf("After: %s (std)\n\n", string);

// 	printf("Before: %s (ft)\n", ft_string);
// 	ft_memmove(ft_string + 7, ft_string, 6);
// 	printf("After: %s (ft)\n", ft_string);
// 	return (0);
// }
