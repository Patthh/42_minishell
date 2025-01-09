#include "../../include/libft.h"

int	ft_printf_string(const char *str)
{
	int		characters_written;

	characters_written = 0;
	if (str == NULL)
	{
		write (1, "(null)", 6);
		characters_written = 6;
	}
	else
	{
		characters_written = write(1, str, ft_strlen(str));
	}
	return (characters_written);
}
