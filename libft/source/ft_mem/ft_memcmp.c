#include "../../include/libft.h"

// compares memory blocks
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	i = 0;
	ptr1 = s1;
	ptr2 = s2;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
		{
			return ((int)ptr1[i] - (int)ptr2[i]);
		}
		i++;
	}
	return (0);
}

// int main(void)
// {
// 	char str1[] = "Hello";
// 	char str2[] = "Hello";
// 	char str3[] = "Bangkok!";

// 	printf("memcmp(str1, str2): %d\n", memcmp(str1, str2, 5));
// 	printf("ft_memcmp(str1, str2): %d\n\n", ft_memcmp(str1, str2, 5));

// 	printf("memcmp(str1, str3): %d\n", memcmp(str1, str3, 5));
// 	printf("ft_memcmp(str1, str3): %d\n", ft_memcmp(str1, str3, 5));

// 	return 0;
// }
