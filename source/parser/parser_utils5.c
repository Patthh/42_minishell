#include "../../include/minishell.h"

static void	sequence_error(char *message, t_program *minishell)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	if (message == NULL)
		ft_putstr_fd("newline", STDERR_FILENO);
	else
		ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	minishell->status = 2;
}

// checks if redirection tokens are followed by a word
static int	sequence_redirection(t_token *token, t_program *minishell)
{
	if (!token->next)
	{
		sequence_error("newline", minishell);
		return (0);
	}
	if (token->next->type != TKN_WORD)
	{
		if (token->next->type == TKN_PIPE)
			sequence_error("|", minishell);
		else if (token->type == TKN_IN)
			sequence_error("<", minishell);
		else if (token->type == TKN_OUT)
			sequence_error(">", minishell);
		else if (token->type == TKN_RDA)
			sequence_error(">>", minishell);
		else
			sequence_error("<<", minishell);
		return (0);
	}
	return (1);
}

// checks if command line starts with a pipe (42-minishell_tester)
static int	sequence_start_pipe(t_token *token, t_program *minishell)
{
	if (token && token->type == TKN_PIPE)
	{
		sequence_error("|", minishell);
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
			sequence_error("|", minishell);
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
