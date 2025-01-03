#include "../../include/minishell.h"

// everything here is for handling the env outside of quotes
// don't touch this, it works now
static void	token_exit(const char **input, t_token **head, t_program *minishell)
{
	char	*value;

	value = ft_itoa(minishell->status);
	token_add(head, token_new(TKN_STATUS, value));
	free (value);
	(*input)++;
}

static void	token_string(const char **input, t_token **head, t_program *minishell)
{
	char	*key;
	char	*value;

	key = env_name(input);
	if (key)
	{
		value = env_value(minishell, key);
		if (value)
			token_add(head, token_new(TKN_ENV, key));
		free (key);
	}
	else
		token_add(head, token_new(TKN_WORD, "$"));
}

// handles special case for $?, retrievew exit status and creates token
// checks if lone $, creates TKN_WORD
// exec commands should update minishell-status
// extract env name if valid
void	token_dollar(const char **input, t_token **head, t_program *minishell)
{
	(*input)++;
	if (**input == '?')
		token_exit(input, head, minishell);
	else if (!ft_isalnum(**input) && **input != '_')
		token_add(head, token_new(TKN_WORD, "$"));
	else
		token_string(input, head, minishell);
}
