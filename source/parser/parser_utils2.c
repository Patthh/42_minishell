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
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

static int	redir_duplicate(t_command *command, int index)
{
	t_redirection	*existing;
	const char		*types[] = {"IN", "OUT", "APPEND", "HEREDOC"};

	if (index == 0 || index == 3)
		existing = command->input;
	else
		existing = command->output;
	while (existing)
	{
		if (ft_strcmp(existing->type, types[index]) == 0)
		{
			ft_putstr_fd("minishell: duplicate redirection\n", STDERR_FILENO);
			return (0);
		}
		existing = existing->next;
	}
	return (1);
}

// input: IN or HEREDOC
// output: OUT or APPEND
static void	redir_add(t_command *command, t_redirection *redirection, int index)
{
	if (index == 0 || index == 3)
	{
		redirection->next = command->input;
		command->input = redirection;
	}
	else
	{
		redirection->next = command->output;
		command->output = redirection;
	}
}

// advances to the next token and check
// check redirection type
// create redirection and add it to command
t_token	*parser_redirection(t_token *token, t_command *command)
{
	const char		*types[] = {"INT", "OUT", "APPEND", "HEREDOC"};
	t_redirection	*redirection;
	int				index;

	index = redir_index(token->type);
	token = token->next;
	if (!redir_filename(token))
		return (NULL);
	if (!redir_duplicate(command, index))
		return (NULL);
	redirection = create_redirection(types[index], token->value);
	redir_add(command, redirection, index);
	return (token->next);
}

