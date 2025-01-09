#include "../../include/libft.h"

// finds the first occurence of a character in a string
// returns a pointer to the first occurrence of the character c in the string s.
char	*ft_strchr(const char *string, int c)
{
	char	target;

	target = (char)c;
	while (*string)
	{
		if (*string == target)
		{
			return ((char *)string);
		}
		string++;
	}
	if (target == '\0')
	{
		return ((char *)string);
	}
	return (NULL);
}

// int main(void)
// {
// 	const char *string = "Hello, World!";
// 	char target = 'W';

// 	printf("%s\n", strchr(string, target));
// 	printf("%s\n", ft_strchr(string, target));
// 	return (0);
// }
