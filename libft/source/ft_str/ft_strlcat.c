#include "../../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	length_dst;
	size_t	length_src;
	size_t	i;
	size_t	j;

	length_dst = ft_strlen(dst);
	length_src = ft_strlen(src);
	i = 0;
	j = 0;
	if (length_dst >= size)
		length_dst = size;
	if (length_dst == size)
		return (size + length_src);
	while (i < size - 1 && dst[i])
	{
		i++;
	}
	while (i < size - 1 && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (length_dst + length_src);
}

// int main(void)
// {
// 	char dst[20] = "Hello, ";
// 	char src[] = "World!";

// 	ft_strlcat(dst, src, sizeof(dst));
// 	printf("Destination: %s\n", dst);

// 	return 0;
// }
