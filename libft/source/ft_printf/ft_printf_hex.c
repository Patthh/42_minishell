#include "../../include/libft.h"

static int	ft_printf_hex_uppercase(unsigned long long x)
{
	const char		*base;
	char			buffer[20];
	int				length;
	int				characters_written;

	length = 0;
	base = "0123456789ABCDEF";
	characters_written = 0;
	if (x == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	while (x != 0)
	{
		buffer[length++] = base[x % 16];
		x /= 16;
	}
	while (length > 0)
	{
		write(1, &buffer[--length], 1);
		characters_written++;
	}
	return (characters_written);
}

static int	ft_printf_hex_lowercase(unsigned long long x)
{
	const char		*base;
	char			buffer[20];
	int				length;
	int				characters_written;

	length = 0;
	base = "0123456789abcdef";
	characters_written = 0;
	if (x == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	while (x != 0)
	{
		buffer[length++] = base[x % 16];
		x /= 16;
	}
	while (length > 0)
	{
		write(1, &buffer[--length], 1);
		characters_written++;
	}
	return (characters_written);
}

int	ft_printf_hex(unsigned long long x, char x_or_x)
{
	if (x_or_x == 'X')
		return (ft_printf_hex_uppercase(x));
	else
		return (ft_printf_hex_lowercase(x));
}
