#include "../../include/libft.h"

char	*ft_strpbrk(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i] != '\0')
	{
		j = 0;
		while (s2[j] != '\0')
		{
			if (s1[i] == s2[j])
			{
				return ((char *)&s1[i]);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

// int main(void)
// {
// 	char *string = "Hello, world";
// 	char *accept = "";

// 	printf("%s\n", strpbrk(string, accept));
// 	printf("%s\n", ft_strpbrk(string, accept));
// 	return (0);
// }
