#include "../../include/minishell.h"

void	token_paranthesis(const char **input, t_token **head)
{
	t_token_type	type;
	const char		*value;

	if (**input == '(')
	{
		type = TKN_START;
		value = "(";
		(*input)++;
	}
	else
	{
		type = TKN_END;
		value = ")";
		(*input)++;
	}
	token_add(head, token_new(type, value));
}
