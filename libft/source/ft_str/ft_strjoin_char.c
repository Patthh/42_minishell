#include "../../include/libft.h"

char	*ft_strjoin_char(const char *str, char c)
{
	char	*result;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	result = malloc(len + 2);
	if (!result)
		return (NULL);
	ft_memcpy(result, str, len);
	result[len] = c;
	result[len + 1] = '\0';
	return (result);
}
