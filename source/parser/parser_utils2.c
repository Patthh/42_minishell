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

static void	redir_free(t_redirection *redirection)
{
	if (redirection)
	{
		free(redirection->filename);
		free(redirection->type);
		free(redirection);
	}
}

// input: IN or HEREDOC
// output: OUT or APPEND
static void	redir_add(t_command *command, t_redirection *redirection, int index)
{
	t_redirection	**list;

	if (index == 0)
		list = &command->input;
	else if (index == 1)
	{
		if (command->output)
			redir_free(command->output);
		command->output = redirection;
		return ;
	}
	else if (index == 2)
	{
		if (command->append)
			redir_free(command->append);
		command->append = redirection;
		return ;
	}
	else
		list = &command->heredoc;
	while (*list)
		list = &(*list)->next;
	*list = redirection;
}

// advances to the next token and check
// check redirection type
// create redirection and add it to command
// in case of multiple redirection,
// each file should be treated as a target
// previous ones are just opened and closed/replaced
// not treated as arguments to the command
t_token	*parser_redirection(t_token *token, t_command *command)
{
	const char		*types[] = {"INT", "OUT", "APPEND", "HEREDOC"};
	t_redirection	*redirection;
	int				index;

	index = redir_index(token->type);
	token = token->next;
	if (!redir_filename(token))
		return (NULL);
	redirection = create_redirection(types[index], token->value);
	if (!redirection)
		return (NULL);
	redir_add(command, redirection, index);
	return (token->next);
}
