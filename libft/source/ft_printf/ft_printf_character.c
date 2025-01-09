#include "../../include/libft.h"

int	ft_printf_character(char c)
{
	if (write(1, &c, 1) == 1)
		return (1);
	else
		return (0);
}
