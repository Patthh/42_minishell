/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:51:35 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:51:36 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
	{
		return (c + 32);
	}
	return (c);
}

// int main(void)
// {
// 	size_t	i = 0;
// 	char 	array[] = {'A', 'a', '1', '!', ' ', 'Z', 'z', '\0'};

// 	while (array[i] != '\0')
// 	{
// 		printf("%c ", tolower(array[i]));
// 		i++;
// 	}

// 	printf("(std)\n");

// 	i = 0;
// 	while (array[i] != '\0')
// 	{
// 		printf("%c ", ft_tolower(array[i]));
// 		i++;
// 	}

// 	printf("(ft)\n");
// 	return (0);
// }
