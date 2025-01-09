#include "../../include/libft.h"

// compares the first n bytes of two strings
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- > 0 && (*s1 || *s2))
	{
		if ((unsigned char)*s1 != (unsigned char)*s2)
		{
			return ((int)((unsigned char)*s1) - (unsigned char)*s2);
		}
		s1++;
		s2++;
	}
	return (0);
}

// int main(void)
// {
// 	const char *s1 = "Hello, Paris!";
// 	const char *s2 = "Hello, Bangkok!";
// 	int n = 10;

// 	printf("strncmp: %d\n", strncmp(s1, s2, n));
// 	printf("ft_strncmp: %d\n", ft_strncmp(s1, s2, n));
// 	return (0);
// }
