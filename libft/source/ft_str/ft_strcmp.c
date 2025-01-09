#include "../../include/libft.h"

// compares two strings
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// int main(void)
// {
// 	char *string1 = "Hello";
// 	char *string2 = "Hello there";

// 	printf("%d\n", strcmp(string1, string2));
// 	printf("%d\n", ft_strcmp(string1, string2));
// 	return (0);
// }
