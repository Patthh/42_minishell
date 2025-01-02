#include "../../include/minishell.h"

int	quote_counter(const char *input)
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

// static void	quote_dollar(const char **input, t_token **head,
// 		t_program *minishell)
// {
// 	char	*value;

// 	(*input)++;
// 	value = env_quote(minishell, *input);
// 	{
// 		if (value)
// 		{
// 			token_add(head, token_new(TKN_ENV, value));
// 			free (value);
// 		}
// 	}
// }

// must handle the env inside double quotes
static void	quote_double(const char **input, t_token **head,
		t_program *minishell)
{
	char		*key;
	char		*value;

	(*input)++;
	while (**input && **input != '"')
	{
		if (**input == '$')
		{
			(*input)++;
			if (**input && (ft_isalnum(**input) || **input == '_'))
			{
				key = env_name(input);
				if (key)
				{
					value = env_value(minishell, key);
					if (value)
						token_add(head, token_new(TKN_ENV, value));
					free (key);
				}
			}
		}
		else
			(*input)++;
	}
	if (**input == '"')
		(*input)++;
}

// everything inside single quote must be handled as a literal string.
// no interpretation or expansion needed (variable expansion or wildcard)
static void	quote_single(const char **input, t_token **head)
{
	char		*value;
	const char	*start;

	start = *input;
	(*input)++;
	while (**input && **input != '\'')
		(*input)++;
	value = ft_strndup(start + 1, *input - start - 1);
	if (value)
	{
		token_add(head, token_new(TKN_WORD, value));
		free (value);
	}
	if (**input == '\'')
		(*input)++;
}

void	token_quotes(const char **input, t_token **head,
		t_program *minishell)
{
	if (**input == '\'')
	{
		quote_single(input, head);
		while (**input == '\'')
			(*input)++;
	}
	else if (**input == '"')
		quote_double(input, head, minishell);
}
