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

static int	strtol_overflow(int sign, char **end, const char *string, long *result)
{
	if (sign == 1)
		*result = LONG_MAX;
	else
		*result = LONG_MIN;
	if (end)
		*end = (char *)string;
	return (0);
}

// converts a string to long integer
long	ft_strtol(const char *string, char **end)
{
	long	result;
	int		sign;
	int		digit;

	string = strtol_parse(string, &sign);
	if (*string)
		return (0);
	while (ft_isdigit(*string))
	{
		digit = *string - '0';
		if (result > LONG_MAX / 10 || (result == LONG_MAX / 10 && digit > 7 - sign * digit))
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
