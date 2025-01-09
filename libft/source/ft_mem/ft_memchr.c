#include "../../include/libft.h"

// searches memory for a byte
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		if (*ptr == (unsigned char)c)
		{
			return ((void *)ptr);
		}
		ptr++;
		i++;
	}
	return (NULL);
}

// int main(void)
// {
// 	const char *s = "Hello, Bangkok!";
// 	char 		c = 'X';
// 	size_t 		n = ft_strlen(s);

// 	char *result = (char *)memchr(s, c, n);
// 	if (result)
// 		printf("Found '%c' at position: %ld (std)\n", c, result - s);
// 	else
// 		printf("Character '%c' not found (std)\n", c);

// 	result = (char *)ft_memchr(s, c, n);
// 	if (result)
// 		printf("Found '%c' at position: %ld (ft)\n", c, result - s);
// 	else
// 		printf("Character '%c' not found (ft)\n", c);
// 	return (0);
// }
