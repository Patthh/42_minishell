/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:49:43 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:49:44 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
	{
		return (1);
	}
	return (0);
}

// int main(void)
// {
// 	char c1 = 'A';
// 	int c2 = 128;
// 	char c3 = 0;
// 	char c4 = '!';

// 	printf("'%c': %d (ft) vs %d (std)\n", c1, ft_isascii(c1), isascii(c1));
// 	printf("%d: %d (ft) vs %d (std)\n", c2, ft_isascii(c2), isascii(c2));
// 	printf("'%c': %d (ft) vs %d (std)\n", c3, ft_isascii(c3), isascii(c3));
// 	printf("'%c': %d (ft) vs %d (std)\n", c4, ft_isascii(c4), isascii(c4));

// 	return 0;
// }
