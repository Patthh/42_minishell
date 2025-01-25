/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:49:38 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:49:39 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	return (0);
}

// int main(void)
// {
// 	char c1 = 'A';
// 	char c2 = '5';
// 	char c3 = '!';
// 	char c4 = ' ';

// 	printf("'%c': %d (ft) vs %d (std)\n", c1, ft_isalnum(c1), isalnum(c1) != 0);
// 	printf("'%c': %d (ft) vs %d (std)\n", c2, ft_isalnum(c2), isalnum(c2) != 0);
// 	printf("'%c': %d (ft) vs %d (std)\n", c3, ft_isalnum(c3), isalnum(c3) != 0);
// 	printf("'%c': %d (ft) vs %d (std)\n", c4, ft_isalnum(c4), isalnum(c4) != 0);

// 	return 0;
// }
