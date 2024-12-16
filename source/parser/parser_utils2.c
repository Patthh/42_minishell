#include "../../include/minishell.h"

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
	t_redirection	*existing;
	int				index;

	index = redir_index(token->type);
	token = token->next;
	if (!token || token->type != TKN_WORD)
		ft_error("Parser: no filename or redirection\n");
	if (index == 0 || index == 3)
		existing = command->input;
	else
		existing = command->output;
	while (existing)
	{
		if (ft_strcmp(existing->type, types[index]) == 0)
			ft_error("Parser: duplicate redirection of same type");
		existing = existing->next;
	}
	redirection = create_redirection(types[index], token->value);
	redir_add(command, redirection, index);
	return (token->next);
}
