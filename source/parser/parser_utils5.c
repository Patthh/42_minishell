#include "../../include/minishell.h"

// checks if redirection tokens are followed by a word
static int	sequence_redirection(t_token *token, t_program *minishell)
{
	if (!token->next)
	{
		error_syntax("newline", minishell);
		return (0);
	}
	if (token->next->type != TKN_WORD)
	{
		if (token->next->type == TKN_PIPE)
			error_syntax("|", minishell);
		else if (token->next->type == TKN_IN)
			error_syntax("<", minishell);
		else if (token->next->type == TKN_OUT)
			error_syntax(">", minishell);
		else if (token->next->type == TKN_RDA)
			error_syntax(">>", minishell);
		else if (token->next->type == TKN_RDH)
			error_syntax("<<", minishell);
		else
			error_syntax(token->next->value, minishell);
		return (0);
	}
	return (1);
}

// checks if command line starts with a pipe (42-minishell_tester)
static int	sequence_start_pipe(t_token *token, t_program *minishell)
{
	if (token && token->type == TKN_PIPE)
	{
		error_syntax("|", minishell);
		return (0);
	}
	return (1);
}

// processes each token
// validates its syntax
static int	sequence_process(t_token *token, int *flag, t_program *minishell)
{
	if (token->type == TKN_WORD)
	{
		*flag = 1;
		return (1);
	}
	if (token->type == TKN_PIPE)
	{
		if (!*flag || !token->next || token->next->type == TKN_PIPE)
		{
			error_syntax("|", minishell);
			return (0);
		}
		*flag = 0;
	}
	else if (token->type == TKN_IN || token->type == TKN_OUT
		|| token->type == TKN_RDA || token->type == TKN_RDH)
	{
		if (!sequence_redirection(token, minishell))
			return (0);
	}
	return (1);
}

int	parser_sequence(t_token *tokens, t_program *minishell)
{
	t_token	*token;
	int		flag;

	token = tokens;
	flag = 0;
	if (!token)
	{
		minishell->status = 0;
		return (1);
	}
	if (!sequence_start_pipe(token, minishell))
		return (0);
	while (token)
	{
		if (!sequence_process(token, &flag, minishell))
			return (0);
		token = token->next;
	}
	return (1);
}
