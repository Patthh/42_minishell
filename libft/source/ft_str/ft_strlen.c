#include "../../include/libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

// int main(void)
// {
// 	const char *str = "Hello, Bangkok!";

// 	printf("strlen: %zu\n", strlen(str));
// 	printf("ft_strlen: %zu\n", ft_strlen(str));
// 	return (0);
// }
