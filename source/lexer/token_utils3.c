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

static char	*process_env(const char **input, t_program *minishell, char *result)
{
	char	*value;
	char	*temp;
	char	*key;

	(*input)++;
	// If $ is at end of input or followed by non-variable character
	if (!**input || **input == '"' || **input == '\'' || !(ft_isalnum(**input) || **input == '_' || **input == '?'))
	{
		temp = ft_strjoin_char(result, '$');
		free(result);
		return temp;
	}

	key = env_name(input);
	if (key)
	{
		value = env_value(minishell, key);
		if (value)
		{
			temp = ft_strjoin(result, value);
			free (result);
			result = temp;
		}
		free (key);
	}
	return (result);
}

// must handle the env inside double quotes
static void	quote_double(const char **input, t_token **head,
		t_program *minishell)
{
	char	*result;
	char	*temp;

	(*input)++;
	result = ft_strdup("");
	while (**input && **input != '"')
	{
		if (**input == '$')
			result = process_env(input, minishell, result);
		else
		{
			temp = ft_strjoin_char(result, **input);
			free (result);
			result = temp;
			if (!result)
				return ;
			(*input)++;
		}
	}
	if (**input == '"')
		(*input)++;
	token_add(head, token_new(TKN_WORD, result));
	free (result);
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
