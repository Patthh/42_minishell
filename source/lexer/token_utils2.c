#include "../../include/minishell.h"

// handles pipe and logical OR
static void	token_pipe(const char **input, t_token **head)
{
	if (*(*input + 1) == '|')
	{
		token_add(head, token_new(TKN_OR, "||"));
		(*input) += 2;
	}
	else
	{
		token_add(head, token_new(TKN_PIPE, "|"));
		(*input)++;
	}
}

// handle background and logical AND
static void	token_ampersand(const char **input, t_token **head)
{
	if (*(*input + 1) == '&')
	{
		token_add(head, token_new(TKN_AND, "&&"));
		(*input) += 2;
	}
	else
	{
		token_add(head, token_new(TKN_BG, "&"));
		(*input)++;
	}
}

// handles redirection tokens
void	token_operator(const char **input, t_token **head)
{
	if (**input == '|')
		token_pipe(input, head);
	else if (**input == '&')
		token_ampersand(input, head);
}

static void	token_string(const char **input, t_token **head, t_program *shell)
{
	char	*key;
	char	*value;

	key = env_name(input);
	if (key)
	{
		value = env_value(shell, key);
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
	char	*status;

	(*input)++;
	if (**input == '?')
	{
		status = ft_itoa(minishell->status);
		token_add(head, token_new(TKN_WORD, status));
		free (status);
		(*input)++;
	}
	else if (**input == '\0' || ft_isspace(**input))
		token_add(head, token_new(TKN_WORD, "$"));
	else if (!ft_isalnum(**input) && **input != '_')
		token_add(head, token_new(TKN_ENV, expand_var(input, minishell)));
	else
		token_string(input, head, minishell);
}
