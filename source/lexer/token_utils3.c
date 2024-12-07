#include "../../include/minishell.h"

void	token_paranthesis(const char **input, t_token **head)
{
	t_token_type	type;
	const char		*value;

	if (**input == '(')
	{
		type = TKN_START;
		value = "(";
	}
	else
	{
		type = TKN_END;
		value = ")";
	}
	token_add(head, token_new(type, value));
}

void	token_quotes(const char **input, t_token **head)
{
	char			c;
	t_token_type	type;
	const char		*start;

	if (c == '\'')
		type = TKN_SINGLE;
	else
		type = TKN_DOUBLE;

	(*input)++;
	start = *input;

	while (**input && **input != c)
		(*input)++;

	// if we reach end of input without closing quote
	// keep the prompt open (like in bash)
	// another while (1) loop?
	if (**input == c)
	{
		// implement strndup to null-terminate the string
		// or use strncpy
	}
}
