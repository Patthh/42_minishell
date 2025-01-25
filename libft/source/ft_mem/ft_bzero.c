/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:50:20 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:50:21 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

// sets a block of memory to zero
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*temp;

	temp = s;
	while (n--)
		*temp++ = 0;
}

// int main(void)
// {
// 	size_t i = 0;
// 	char buffer[10];
// 	char ft_buffer[10];

// 	memset(buffer, '1', sizeof(buffer));
// 	ft_memset(ft_buffer, '1', sizeof(ft_buffer));

// 	printf("Before: ");
// 	while (i < sizeof(buffer))
// 	{
// 		printf("%c", buffer[i]);
// 		i++;
// 	}
// 	printf(" (std)\n");

// 	i = 0;
// 	printf("Before: ");
// 	while (i < sizeof(ft_buffer))
// 	{
// 		printf("%c", ft_buffer[i]);
// 		i++;
// 	}
// 	printf(" (ft)\n\n");

// 	bzero(buffer, sizeof(buffer));
// 	ft_bzero(ft_buffer, sizeof(ft_buffer));

// 	i = 0;
// 	printf("After: ");
// 	while (i < sizeof(buffer))
// 	{
// 		printf("%d", buffer[i]);
// 		i++;
// 	}
// 	printf(" (std)\n");

// 	i = 0;
// 	printf("After: ");
// 	while (i < sizeof(ft_buffer))
// 	{
// 		printf("%d", ft_buffer[i]);
// 		i++;
// 	}
// 	printf(" (ft)\n");
// 	return (0);
// }
