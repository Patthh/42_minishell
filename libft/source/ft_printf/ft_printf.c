#include "../../include/libft.h"

int	ft_printf_format(va_list args, char format)
{
	int	print_length;

	if (format == 'c')
		print_length = ft_printf_character(va_arg(args, int));
	else if (format == 'x' || format == 'X')
		print_length = ft_printf_hex(va_arg(args, unsigned int), format);
	else if (format == 'd' || format == 'i')
		print_length = ft_printf_number(va_arg(args, int));
	else if (format == 'p')
		print_length = ft_printf_pointer(va_arg(args, void *));
	else if (format == 's')
		print_length = ft_printf_string(va_arg(args, const char *));
	else if (format == 'u')
		print_length = ft_printf_unsigned_number(va_arg(args, unsigned int));
	else if (format == '%')
		print_length = ft_printf_character('%');
	else
		print_length = 0;
	return (print_length);
}

int	ft_printf(const char *str, ...)
{
	int			i;
	int			total_characters;
	va_list		args;

	i = 0;
	total_characters = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			total_characters += ft_printf_format(args, str[i + 1]);
			i++;
		}
		else
			total_characters += ft_printf_character(str[i]);
		i++;
	}
	va_end(args);
	return (total_characters);
}
