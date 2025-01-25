/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:49:51 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:49:52 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
	{
		return (1);
	}
	return (0);
}

// int main(void)
// {
// 	char c1 = 'A';
// 	char c2 = ' ';
// 	char c3 = '\0';
// 	char c4 = '!';

// 	printf("'%c': %d (ft) vs %d (std)\n", c1, ft_isprint(c1), isprint(c1) != 0);
// 	printf("'%c': %d (ft) vs %d (std)\n", c2, ft_isprint(c2), isprint(c2) != 0);
// 	printf("'%c': %d (ft) vs %d (std)\n", c3, ft_isprint(c3), isprint(c3) != 0);
// 	printf("'%c': %d (ft) vs %d (std)\n", c4, ft_isprint(c4), isprint(c4) != 0);

// 	return 0;
// }
