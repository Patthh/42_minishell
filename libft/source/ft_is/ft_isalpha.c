#include "../../include/libft.h"

int	ft_isalpha(int c)

{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	return (0);
}

// int main(void)
// {
// 	char c1 = 'A';
// 	char c2 = 'b';
// 	char c3 = '1';
// 	char c4 = '!';

// 	printf("'%c': %d (ft) vs %d (std)\n", c1, ft_isalpha(c1), isalpha(c1) != 0);
// 	printf("'%c': %d (ft) vs %d (std)\n", c2, ft_isalpha(c2), isalpha(c2) != 0);
// 	printf("'%c': %d (ft) vs %d (std)\n", c3, ft_isalpha(c3), isalpha(c3) != 0);
// 	printf("'%c': %d (ft) vs %d (std)\n", c4, ft_isalpha(c4), isalpha(c4) != 0);

// 	return 0;
// }
