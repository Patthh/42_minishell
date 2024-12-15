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
	while (*end && (ft_isalnum(*end) || *end == '_'))
		end++;
	if (start == end)
		return (NULL);
	return (ft_strndup(start, end - start));
}

// retrieve env value
char	*env_value(t_program *minishell, const char *key)
{
	t_env	*current;

	current = minishell->env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (getenv(key));
}

// create token for env
void	env_token(t_token **head, t_program *minishell, const char *key)
{
	char	*value;

	value = env_value(minishell, key);
	if (value)
		token_add(head, token_new(TKN_ENV, value));
}

char	*env_quote(t_program *minishell, const char *input)
{
	char	*key;
	char	*value;

	key = env_name(&input);
	if (!key)
		return (NULL);
	value = env_value(minishell, key);
	free(key);
	if (value)
		return (ft_strdup(value));
	else
		return (NULL);
}

// handles special case for $?, retrievew exit status and creates token
// checks if lone $, creates TKN_WORD
// exec commands should update minishell-status
// extract env name if valid
void	token_dollar(const char **input, t_token **head, t_program *minishell)
{
	char	*key;
	char	*value;

	(*input)++;
	if (**input == '?')
	{
		value = ft_itoa(minishell->status);
		token_add(head, token_new(TKN_STATUS, value));
		free (value);
		(*input)++;
		return ;
	}
	if (!ft_isalnum(**input) && **input != '_')
	{
		token_add(head, token_new(TKN_WORD, "$"));
		return ;
	}
	key = env_name(input);
	if (key)
	{
		value = env_value(minishell, key);
		if (value)
			token_add(head, token_new(TKN_ENV, value));
		free (key);
	}
}
