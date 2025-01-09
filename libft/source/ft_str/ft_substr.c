#include "../../include/libft.h"

// extracts a substring
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	src_len;

	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	if (start >= src_len)
	{
		substring = ft_calloc(1, sizeof(char));
		if (!substring)
			return (NULL);
		return (substring);
	}
	if (len > src_len - start)
		len = src_len - start;
	substring = ft_calloc(len + 1, sizeof(char));
	if (!substring)
		return (NULL);
	ft_memcpy(substring, s + start, len);
	return (substring);
}

// int main(void)
// {
// 	printf("%s\n", ft_substr("Hello, Bangkok!", 7, 3));
// 	printf("%s\n", ft_substr("Hello, Bangkok!", 10, 4));
// 	return (0);
// }
