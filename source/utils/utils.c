#include "../../include/minishell.h"

void	ft_error(const char *message)
{
	ft_putstr_fd((char *)message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	ft_isnumeric(const char *string)
{
	while (*string)
	{
		if (!ft_isdigit(*string))
			return (0);
		string++;
	}
	return (1);
}

int	ft_isspecial(char c)
{
	const char	*special_chars = "!@#$%^&*()-_=+[]{}|;:,.<>?/~`";

	while (*special_chars)
	{
		if (c == *special_chars)
			return (1);
		special_chars++;
	}
	return (0);
}
