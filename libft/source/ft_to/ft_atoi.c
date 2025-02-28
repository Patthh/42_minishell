/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:51:32 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:51:33 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

// converts a string to an integer
int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * result);
}

// int	main(void)
// {
// 	const char	*array[] = {"42", "   -42", "   +42", "0",
// 		"123abc", "-123abc", "abc123", NULL};
// 	int i;
// 	// Loop for standard atoi
// 	i = 0;
// 	while (array[i])
// 	{
// 		printf("%d ", atoi(array[i]));
// 		i++;
// 	}
// 	printf("(std)\n");
// 	i = 0;
// 	while (array[i])
// 	{
// 		printf("%d ", ft_atoi(array[i]));
// 		i++;
// 	}
// 	printf("(ft)\n");
// 	return (0);
// }
