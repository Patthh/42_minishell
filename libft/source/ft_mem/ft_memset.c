#include "../../include/libft.h"

// fills memory with a constant byte
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*temp;
	unsigned char	*end;

	temp = (unsigned char *)s;
	end = temp + n;
	while (temp < end)
		*temp++ = c;
	return (s);
}

// int	main(void)
// {
// 	char	buffer[10];
// 	char	ft_buffer[10];
// 	size_t	i = 0;

// 	memset(buffer, 'X', sizeof(buffer));
// 	ft_memset(ft_buffer, 'X', sizeof(ft_buffer));

// 	i = 0;
// 	while (i < sizeof(buffer))
// 	{
// 		printf("%c", buffer[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	i = 0;
// 	while (i < sizeof(ft_buffer))
// 	{
// 		printf("%c", ft_buffer[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	return (0);
// }
