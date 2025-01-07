#include "../../include/minishell.h"

// handles input and heredoc redirections
static void	token_input(const char **input, t_token **head)
{
	if (*(*input + 1) == '<')
	{
		token_add(head, token_new(TKN_RDH, "<<"));
		(*input) += 2;
	}
	else
	{
		token_add(head, token_new(TKN_IN, "<"));
		(*input)++;
	}
}

// handles output and append redirections
static void	token_output(const char **input, t_token **head)
{
	if (*(*input + 1) == '>')
	{
		token_add(head, token_new(TKN_RDA, ">>"));
		(*input) += 2;
	}
	else
	{
		token_add(head, token_new(TKN_OUT, ">"));
		(*input)++;
	}
}

// handles redirection tokens
void	token_redirector(const char **input, t_token **head)
{
	if (**input == '<')
		token_input(input, head);
	else if (**input == '>')
		token_output(input, head);
}

// extracts and creates a token for a word
t_token	*token_word(const char **input)
{
	const char	*start;
	char		*word;
	t_token		*token;

	start = *input;
	while (**input && !ft_isspace(**input))
		(*input)++;
	word = ft_strndup(start, *input - start);
	token = token_new(TKN_WORD, word);
	free(word);
	return (token);
}
