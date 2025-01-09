#include "../../include/libft.h"

// duplicates a string
char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dest;

	i = ft_strlen(s);
	dest = malloc(i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// int main(void)
// {
// 	const char *string = "Hello, Bangkok!";

// 	char *dup = strdup(string);
// 	if (dup)
// 	{
// 		printf("%s (std)\n", dup);
// 		free(dup);
// 	}
// 	else
// 		printf("Failed (std)\n");

// 	char *ft_dup = ft_strdup(string);
// 	if (ft_dup)
// 	{
// 		printf("%s (ft)\n", ft_dup);
// 		free(ft_dup);
// 	}
// 	else
// 		printf("Failed (ft)\n");
// 	return (0);
// }
