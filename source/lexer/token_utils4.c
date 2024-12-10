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
			single_quote++;
		else if (*input == '"')
			double_quote++;
		input++;
	}
	return (single_quote % 2 == 0 && double_quote % 2 == 0);
}

static void	dollar_sign(const char **input, t_token **head, const char **start)
{
	char	*value;

	value = ft_strndup(*start, *input - *start);
	token_add(head, token_new(TKN_WORD, value));
	free (value);
	// handle_dollar(input, head);
	*start = *input;
}

static void	quote_single(const char **input, t_token **head)
{
	const char	*start;
	char		*value;

	start = ++(*input);
	while (**input && **input != '\'')
		(*input)++;
	if (**input == '\'')
	{
		token_add(head, token_new(TKN_SINGLE, "'"));
		value = ft_strndup(start, *input - start);
		token_add(head, token_new(TKN_WORD, value));
		free(value);
		token_add(head, token_new(TKN_SINGLE, "'"));
		(*input)++;
	}
}

static void	quote_double(const char **input, t_token **head)
{
	const char	*start;
	char		*value;

	start = ++(*input);
	while (**input && **input != '"')
	{
		if (**input == '$')
			dollar_sign(input, head, &start);
		else
			(*input)++;
	}
	if (**input == '"')
	{
		token_add(head, token_new(TKN_DOUBLE, "\""));
		value = ft_strndup(start, *input - start);
		token_add(head, token_new(TKN_WORD, value));
		free(value);
		token_add(head, token_new(TKN_DOUBLE, "\""));
		(*input)++;
	}
}

void	token_quotes(const char **input, t_token **head)
{
	if (!quote_counter(*input))
		return ;
	if (**input == '\'')
		quote_single(input, head);
	else if (**input == '"')
		quote_double(input, head);
}
