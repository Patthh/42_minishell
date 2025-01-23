#include "../../include/minishell.h"

// extract env name
char	*env_name(const char **input)
{
	const char	*start;
	const char	*end;

	while (**input == '$')
		(*input)++;
	start = *input;
	end = start;
	while (*end && (ft_isalnum(*end) || *end == '_'
			|| *end == '-' || *end == '.'))
		end++;
	if (start == end)
		return (NULL);
	*input = end;
	return (ft_strndup(start, end - start));
}

// retrieve env value
char	*env_value(t_program *minishell, const char *key)
{
	t_env	*current;

	if (!key)
		return (NULL);
	current = minishell->env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (getenv(key));
}

// Helper function to handle environment variable expansion
void	env_word(const char **input, char **result, t_program *minishell)
{
	char	*key;
	char	*value;

	(*input)++;
	if (**input && (ft_isalnum(**input) || **input == '_' || **input == '?'))
	{
		key = env_name(input);
		value = env_value(minishell, key);
		if (value)
			*result = token_join(*result, value);
		free(key);
	}
	else if (**input == '?')
	{
		value = ft_itoa(minishell->status);
		if (value)
			*result = token_join(*result, value);
		free(value);
		(*input)++;
	}
	else
	{
		*result = token_join(*result, "$");
	}
}

// Handle environment variables
void	token_env(const char **input, t_token **head, t_program *shell)
{
	char	*key;
	char	*value;

	key = env_name(input);
	if (key)
	{
		value = env_value(shell, key);
		if (value)
			token_add(head, token_new(TKN_ENV, key));
		else
			token_add(head, token_new(TKN_WORD, ""));
		free(key);
	}
	else
		token_add(head, token_new(TKN_WORD, "$"));
}
