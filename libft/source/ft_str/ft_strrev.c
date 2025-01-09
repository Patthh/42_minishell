#include "../../include/libft.h"

char	*ft_strrev(char *str)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = 0;
	while (str[end] != '\0')
		end++;
	end--;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
	return (str);
}
