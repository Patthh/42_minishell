#include "../../include/libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
	{
		return (c - 32);
	}
	return (c);
}

// int main(void)
// {
// 	size_t	i = 0;
// 	char 	array[] = {'A', 'a', '1', '!', ' ', 'Z', 'z', '\0'};

// 	while (array[i] != '\0')
// 	{
// 		printf("%c ", toupper(array[i]));
// 		i++;
// 	}

// 	printf("(std)\n");

// 	i = 0;
// 	while (array[i] != '\0')
// 	{
// 		printf("%c ", ft_toupper(array[i]));
// 		i++;
// 	}

// 	printf("(ft)\n");
// 	return (0);
// }
