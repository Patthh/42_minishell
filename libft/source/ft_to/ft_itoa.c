/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:51:34 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:51:35 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static size_t	ft_intlen(int n)
{
	size_t	length;

	length = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		length++;
	while (n != 0)
	{
		length++;
		n /= 10;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	size_t	length;
	char	*string;
	long	number;

	length = ft_intlen(n);
	string = (char *)malloc(length + 1);
	if (!string)
		return (NULL);
	string[length] = '\0';
	number = n;
	if (number < 0)
	{
		string[0] = '-';
		number = -number;
	}
	if (number == 0)
		string[0] = '0';
	while (number)
	{
		string[--length] = (number % 10) + '0';
		number /= 10;
	}
	return (string);
}

// int	main(void)
// {
// 	char *str1 = ft_itoa(INT_MAX);
// 	char *str2 = ft_itoa(0);
// 	char *str3 = ft_itoa(INT_MIN);

// 	printf("%s\n", str1);
// 	printf("%s\n", str2);
// 	printf("%s\n", str3);

// 	free(str1);
// 	free(str2);
// 	free(str3);

// 	return (0);
// }
