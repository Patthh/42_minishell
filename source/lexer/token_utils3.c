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

/*
 * detects the quote type ' or "
 * use helper function for handling single or double quotes
 * helper functions must collect content inside quotes
 * double quote handles $VAR and $? expansions
 * extract and replace env tokens with their values from t_env
 *
 * bash behaviour with quotes
 * interactive shell, bash waits for the closing quote on the next line
 * 		use readline until closing quote is found
 * non-interative shell, bash throws syntax error and stops execution
 */
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
	if (**input == c)
	{
		in_quote(head, type, start, *input);
	}
}


void	in_quote(t_token **head, t_token_type type, const char *start, const char *end)
{
	size_t	length;
	char	*value;

	length = end - start;
	value = ft_strndup(start, length);
	token_add(head, token_new(type, value));
	free (value);
}
