#include "../../include/libft.h"

// locates a substring in a string
// returns big if little is empty
// returns NULL if little isn't in big
// returns pointer to first occurrence
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		length_little;

	length_little = ft_strlen(little);
	if (*little == '\0')
	{
		return ((char *)big);
	}
	while (*big && len >= length_little)
	{
		if (ft_strncmp(big, little, length_little) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
// int main(void)
// {
// 	const char *big = "Hello, Bangkok!";
// 	const char *little = "Bang";
// 	size_t		length = 15;

// 	printf("ft_strnstr: %s\n", ft_strnstr(big, little, length));
// 	return (0);
// }
