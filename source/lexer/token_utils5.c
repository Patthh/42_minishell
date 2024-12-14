#include "../../include/minishell.h"

// static void	token_env(const char **input, t_token **head, t_program *minishell)
// {
// 	char	*key;
// 	char	*value;

// 	key = env_name(input);
// 	if (key)
// 	{
// 		value = env_value(minishell, key);
// 		if (value)
// 			token_add(head, token_new(TKN_ENV, value));
// 		free (key);
// 	}
// }

// for this to work, exec commands should update minishell->status
// static void	token_exit(const char **input, t_token **head, t_program *minishell)
// {
// 	char	*status;

// 	(*input)++;
// 	if (**input == '?')
// 	{
// 		status = ft_itoa(minishell->status);
// 		if (status)
// 		{
// 			token_add(head, token_new(TKN_STATUS, status));
// 			free(status);
// 		}
// 		(*input)++;
// 	}
// }

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

void	token_wildcard(const char **input, t_token **head)
{
	if (**input == '*')
	{
		token_add(head, token_new(TKN_WILDCARD, "*"));
		(*input)++;
		return ;
	}
}
