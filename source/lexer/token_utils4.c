#include "../../include/minishell.h"

// tracks open/closed single and double quotes
int	quote_tracker(const char *input)
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

// create token for env
void	env_token(t_token **head, t_program *minishell, const char *key)
{
	char	*value;

	value = env_value(minishell, key);
	if (value)
		token_add(head, token_new(TKN_ENV, value));
}

