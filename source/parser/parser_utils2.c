#include "../../include/minishell.h"

// finds index of redirection type
static int	redir_index(t_token_type token_type)
{
	const t_token_type	type[] = {TKN_IN, TKN_OUT, TKN_RDA, TKN_RDH};
	int					i;

	i = 0;
	while (i < 4)
	{
		if (token_type == type[i])
			return (i);
		i++;
	}
	return (-1);
}

// checks next token is a TKN_WORD
static int	redir_filename(t_token *token)
{
	if (!token || token->type != TKN_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

// input: IN or HEREDOC
// output: OUT or APPEND
static void	redir_add(t_command *command, t_redirection *redirection, int index)
{
	t_redirection	**list;
	// t_redirection	*temp;
	if (index == 0)
		list = &command->input;
	else if (index == 1)
		list = &command->output;
	else if (index == 2)
		list = &command->append;
	else
		list = &command->heredoc;
	while (*list)
		list = &(*list)->next;
	*list = redirection;
}

// advances to the next token and check
// check redirection type
// create redirection and add it to command
t_token	*parser_redirection(t_token *token, t_command *command)
{
	const char		*types[] = {"INT", "OUT", "APPEND", "HEREDOC"};
	t_redirection	*redirection;
	t_token			*next;
	int				index;

	index = redir_index(token->type);
	token = token->next;
	if (!redir_filename(token))
		return (NULL);
	next = token->next;
	if (next && (next->type == TKN_OUT || next->type == TKN_RDA))
	{
		if (!parser_argument(command, token->value))
			ft_error("Parser: Failed to add argument\n");
		return (token->next);
	}
	redirection = create_redirection(types[index], token->value);
	if (!redirection)
		return (NULL);
	redir_add(command, redirection, index);
	return (token->next);
}

int	parser_sequence(t_token *tokens)
{
	t_token	*token;

	token = tokens;
	while (token)
	{
		if (token->type == TKN_PIPE && (!token->next || token->next->type == TKN_PIPE))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
			return (0);
		}
		if ((token->type == TKN_IN || token->type == TKN_OUT || token->type == TKN_RDA || token->type == TKN_RDH) && (!token->next || token->next->type != TKN_WORD))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
			return (0);
		}
		token = token->next;
	}
	return (1);
}
