#include "../../include/minishell.h"

// skips whitespaces and extracts sign
static const char	*strtol_parse(const char *string, int *sign)
{
	while (ft_isspace(*string))
		string++;
	*sign = 1;
	if (*string == '-')
	{
		*sign = -1;
		string++;
	}
	else if (*string == '+')
		string++;
	return (string);
}

static int	strtol_overflow(int sign, char **end, const char *string,
		long *result)
{
	if (sign == 1)
		*result = LONG_MAX;
	else
		*result = LONG_MIN;
	if (end)
		*end = (char *)string;
	errno = ERANGE;
	return (0);
}

// converts a string to long integer
long	ft_strtol(const char *string, char **end)
{
	long	result;
	int		sign;
	int		digit;

	result = 0;
	string = strtol_parse(string, &sign);
	if (!ft_isdigit(*string))
		return (0);
	while (ft_isdigit(*string))
	{
		digit = *string - '0';
		if (result > LONG_MAX / 10
			|| (result == LONG_MAX / 10 && digit > 7 - sign * digit))
		{
			strtol_overflow(sign, end, string, &result);
			return (result);
		}
		result = result * 10 + digit;
		string++;
	}
	if (end)
		*end = (char *)string;
	return (result * sign);
}

// int main(void)
// {
// 	char *end;
// 	long result;
// 	// Test cases
// 	result = ft_strtol("777", &end);
// 	printf("Result: %ld, End: %s\n", result, end); // Expected: 777, ""
// 	result = ft_strtol("-123", &end);
// 	printf("Result: %ld, End: %s\n", result, end); // Expected: -123, ""
// 	result = ft_strtol("2147483648", &end); // Assuming LONG_MAX is 2147483647
// 	printf("Result: %ld, End: %s\n", result, end);
// }
