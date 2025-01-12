#include "../../include/minishell.h"

// tracks open/closed single and double quotes
int	quote_tracker(const char *input)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*input)
	{
		if (*input == '\'')
		{
			if (!double_quote)
				single_quote = !single_quote;
		}
		else if (*input == '"')
		{
			if (!single_quote)
				double_quote = !double_quote;
		}
		input++;
	}
	return (!(single_quote || double_quote));
}

// tracks open/closed parentheses
int	parentheses_tracker(const char *input)
{
	int	parentheses;

	parentheses = 0;
	while (*input)
	{
		if (*input == '(')
			parentheses++;
		else if (*input == ')')
		{
			if (parentheses == 0)
				return (0);
			parentheses--;
		}
		input++;
	}
	return (parentheses == 0);
}
