#include "../../include/libft.h"

// applies a function to each character of a string, modifying it in place
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		f(i, s);
		i++;
		s++;
	}
	return ;
}

// static void	capitalizer(unsigned int index, char *c)
// {
// 	(void)index;
// 	if (*c >= 'a' && *c <= 'z')
// 		*c -= 32;
// }

// int main(void)
// {
// 	char string[] = "Hello, Bangkok!";

// 	ft_striteri(string, capitalizer);
// 	printf("%s\n", string);
// 	return (0);
// }
