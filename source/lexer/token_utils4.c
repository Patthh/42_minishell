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
	return !(single_quote || double_quote);
}
/*
 * everything inside single quote must be handled as a literal string.
 * no interpretation or expansion needed (variable expansion or wildcard)
 */
static void	quote_single(const char **input, t_token **head)
{
	const char	*start;
	char		*value;

	start = ++(*input);

	while (**input && **input != '\'')
		(*input)++;

	if (**input == '\0')
		return ;

	if (**input == '\'')
	{
		if (start < *input)
		{
			value = ft_strndup(start, *input - start);
			if (value && *value != '\0')
			{
				token_add(head, token_new(TKN_WORD, value));
				free (value);
			}
		}
		(*input)++;
	}
}

static void	quote_merged(char **value, const char *content)
{
	char	*new_value;

	if (*value)
	{
		new_value = (ft_strjoin(*value, content));
		free(value);
		*value = new_value;
	}
	else
		*value = ft_strdup(content);
}

static void	quote_expansion(const char **input, t_token **head, t_program *minishell, char **value)
{
	const char	*start;
	char		*value_expanded;

	start = *input + 1;
	value_expanded = variable_expand(input, head, minishell, &start);
	if (value_expanded)
	{
		quote_merged(value, value_expanded);
		free(value_expanded);
	}
	*input = start;
}

static void	quote_double(const char **input, t_token **head, t_program *minishell)
{
	const char	*start;
	char		*value;
	char		*remain;

	start = ++(*input);
	value = NULL;
	while (**input && **input != '"')
	{
		if (**input == '$')
			quote_expansion(input, head, minishell, &value);
		else
			(*input)++;
	}
	if (start < *input)
	{
		remain = ft_strndup(start, *input - start);
		quote_merged(&value, remain);
		free(remain);
	}
	if (**input == '"')
	{
		if (value && *value != '\0')
			token_add(head, token_new(TKN_WORD, value));
		free(value);
		(*input)++;
	}
}


void	token_quotes(const char **input, t_token **head, t_program *minishell)
{
	if (!quote_counter(*input))
		return ;
	if (**input == '\'')
		quote_single(input, head);
	else if (**input == '"')
		quote_double(input, head, minishell);
}
