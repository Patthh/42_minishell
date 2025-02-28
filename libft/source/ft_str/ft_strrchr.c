/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:51:16 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:51:17 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

// locates character in string
// returns pointer to last matched character or NULL if not
char	*ft_strrchr(const char *s, int c)
{
	char	first_character;
	int		i;
	int		last_character;

	first_character = (char)c;
	i = 0;
	last_character = -1;
	while (s[i] != '\0')
	{
		if (s[i] == first_character)
		{
			last_character = i;
		}
		i++;
	}
	if (first_character == '\0' && last_character == -1)
	{
		return ((char *)(s + i));
	}
	if (last_character != -1)
	{
		return ((char *)(s + last_character));
	}
	return (NULL);
}

// int	main(void)
// {
// 	const char *string = "Hello, Bangkok!";
// 	char c = 'o';

// 	printf("strrchr: %s\n", strrchr(string, c));
// 	printf("ft_strrchr: %s\n", ft_strrchr(string, c));
// 	return (0);
// }
