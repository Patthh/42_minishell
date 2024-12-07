#include "../../include/minishell.h"

// handles redirection tokens
void	token_operator(const char **input, t_token **head)
{
	if (**input == '|')
		token_pipe(input, head);
	else if (**input == '&')
		token_ampersand(input, head);
}

// handles pipe and logical OR
static void	token_pipe(const char **input, t_token **head)
{
	if (*(*input + 1) == '|')
	{
		token_add(input, token_new(TKN_OR, "||"));
		(*input) += 2;
	}
	else
	{
		token_add(input, token_new(TKN_PIPE, "|"));
		(*input)++;
	}
}

// handle background and logical AND
static void	token_ampersand(const char **input, t_token **head)
{
	if (*(*input + 1) == '&')
	{
		token_add(input, token_new(TKN_AND, "&&"));
		(*input) += 2;
	}
	else
	{
		token_add(input, token_new(TKN_BG, "&"));
		(*input)++;
	}
}
