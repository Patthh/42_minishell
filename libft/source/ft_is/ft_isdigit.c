#include "../../include/libft.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
	{
		return (1);
	}
	return (0);
}

// int main(void)
// {
// 	char c1 = '0';
// 	char c2 = '5';
// 	char c3 = 'a';
// 	char c4 = '!';

// 	printf("'%c': %d (ft) vs %d (std)\n", c1, ft_isdigit(c1), isdigit(c1) != 0);
// 	printf("'%c': %d (ft) vs %d (std)\n", c2, ft_isdigit(c2), isdigit(c2) != 0);
// 	printf("'%c': %d (ft) vs %d (std)\n", c3, ft_isdigit(c3), isdigit(c3) != 0);
// 	printf("'%c': %d (ft) vs %d (std)\n", c4, ft_isdigit(c4), isdigit(c4) != 0);

// 	return 0;
// }
