#include "../../include/libft.h"

static int	handle_digit(char c, int str_base)
{
	int	value;

	value = -1;
	if (c >= 'A' && c <= 'F')
		c += 32;
	if (c >= '0' && c <= '9')
		value = c - '0';
	if (c >= 'a' && c <= 'f')
		value = 10 + c - 'a';
	if (value < str_base)
		return (value);
	return (-1);
}

static int	handle_sign(const char *string, int *i)
{
	int	sign;

	sign = 1;
	if (string[*i] == '-' || string[*i] == '+')
	{
		if (string[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	i;
	int	sign;
	int	result;
	int	digit;

	i = 0;
	sign = 1;
	result = 0;
	digit = 0;
	if (str == NULL || str_base < 2 || str_base > 16)
		return (0);
	sign = handle_sign(str, &i);
	digit = handle_digit(str[i], str_base);
	while (digit != -1)
	{
		result = result * str_base + digit;
		i++;
		digit = handle_digit(str[i], str_base);
	}
	return (result * sign);
}

// int main(void)
// {
// 	const char *string = "abcdef"; // 11259375
// 	int base = 16;

// 	printf("%d\n", ft_atoi_base(string, base));
// 	return (0);
// }
