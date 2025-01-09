#include "../../include/libft.h"

// duplicates the first 'n' character of 'src' into 'dest'
char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	char	*dest;

	i = 0;
	j = 0;
	if (!src)
		return (NULL);
	while (src[i] != '\0' && i < n)
		i++;
	dest = malloc(i + 1);
	if (!dest)
		return (NULL);
	while (j < i)
	{
		dest[j] = src[j];
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
