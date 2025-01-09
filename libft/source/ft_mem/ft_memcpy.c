#include "../../include/libft.h"

// copies memory
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*temp_dest;
	const unsigned char	*temp_src;
	size_t				i;

	if (!dest && !src && n > 0)
		return (NULL);
	if (!n)
		return (dest);
	temp_dest = (unsigned char *)dest;
	temp_src = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		temp_dest[i] = temp_src[i];
		i++;
	}
	return (dest);
}

// int main(void)
// {
// 	char src[] = "Hello, Bangkok!";
// 	char dst[50];
// 	char ft_dst[50];

// 	memcpy(dst, src, strlen(src) + 1);
// 	ft_memcpy(ft_dst, src, ft_strlen(src) + 1);

// 	printf("%s (std)\n", dst);
// 	printf("%s (ft)\n", ft_dst);
// 	return (0);
// }
