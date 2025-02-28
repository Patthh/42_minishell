/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:51:09 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:51:10 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

// applies a function to each character of a string to create a new string
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	i = 0;
	str = (char *)malloc(ft_strlen(s) + 1);
	if (str == NULL)
	{
		return (NULL);
	}
	while (s[i])
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

// static char	capitalizer(unsigned int index, char c)
// {
// 	(void)index;
// 	if (c >= 'a' && c <= 'z')
// 		c -= 32;
// 	return (c);
// }

// int main(void)
// {
// 	char string1[] = "Hello, Bangkok!";
// 	char *string2 = ft_strmapi(string1, capitalizer);

// 	printf("string1: %s\n", string1);
// 	printf("string2: %s\n", string2);
// 	free(string2);
// 	return (0);
// }
