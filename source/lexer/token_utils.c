#include "../../include/minishell.h"

// handles redirection tokens
void	token_redirector(const char **input, t_token **head)
{
	if (**input == '<')
		token_input(input, head);
	else if (**input == '>')
		token_output(input, head);
}

// handles input and heredoc redirections
static void	token_input(const char **input, t_token **head)
{
	if (*(*input + 1) == '<')
	{
		token_add(input, token_new(TKN_RDH, "<<"));
		(*input) += 2;
	}
	else
	{
		token_add(input, token_new(TKN_IN, "<"));
		(*input)++;
	}
}

// handles output and append redirections
static void	token_output(const char **input, t_token **head)
{
	if (*(*input + 1) == '>')
	{
		token_add(input, token_new(TKN_RDA, ">>"));
		(*input) += 2;
	}
	else
	{
		token_add(input, token_new(TKN_OUT, ">"));
		(*input)++;
	}
}
