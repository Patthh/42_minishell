#include "../../include/libft.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i] != '\0')
	{
		j = 0;
		while (reject[j] != '\0')
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

// int main(void)
// {
// 	const char *string = "Hello, word!";
// 	const char *reject = "apq";

// 	printf("%lu\n", strcspn(string, reject));
// 	printf("%lu\n", ft_strcspn(string, reject));
// 	return (0);
// }
