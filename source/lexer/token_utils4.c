#include "../../include/minishell.h"

void	token_unquoted(const char **input, char **result,
	t_program *minishell)
{
	while (**input && !ft_isspace(**input) && **input != '\'' && **input != '"')
	{
		if (**input == '$')
			env_word(input, result, minishell);
		else
			word_regular(input, result);
	}
}

// Process content within double quotes and handle variable expansion
void	token_double(const char **input, char **result, t_program *minishell)
{
	(*input)++;
	while (**input && **input != '"')
	{
		if (**input == '$')
			env_word(input, result, minishell);
		else
			word_regular(input, result);
	}
	if (**input == '"')
		(*input)++;
}

// process content within single quotes
// treat as literal
void	token_single(const char **input, char **result)
{
	const char	*start;
	char		*content;

	(*input)++;
	start = *input;
	while (**input && **input != '\'')
		(*input)++;
	if (**input)
	{
		content = ft_strndup(start, *input - start);
		*result = word_join(*result, content);
		free(content);
		(*input)++;
	}
}

void	token_assign(const char **input, t_token **head)
{
	char	*key;
	char	*value;

	key = ft_strndup(*input, ft_strchr(*input, '=') - *input);
	(*input) = ft_strchr(*input, '=') + 1;
	value = ft_strdup(*input);
	while (**input && !ft_isspace(**input))
		(*input)++;
	token_add(head, token_new(TKN_ASSIGN, ft_strjoin(key, value)));
	free(key);
	free(value);
}
