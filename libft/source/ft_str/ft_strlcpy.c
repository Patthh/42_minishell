#include "../../include/libft.h"
#include <bsd/string.h>
#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size)
{
	size_t	i;

	i = 0;
	if (dst_size == 0)
	{
		return (ft_strlen(src));
	}
	while (src[i] != '\0' && i < dst_size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (i < dst_size)
	{
		dst[i] = '\0';
	}
	else if (dst_size > 0)
	{
		dst[dst_size - 1] = '\0';
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

// int main(void)
// {
// 	char src[] = "Hello, World!";
// 	char dst[20];
// 	ft_strlcpy(dst, src, sizeof(dst));
// 	printf("%s\n", dst);
// 	return 0;
// }
