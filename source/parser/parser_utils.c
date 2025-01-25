#include "../../include/minishell.h"

// parse token and build commands
// update command and pipeline as needed
t_token	*parser_token(t_token *token, t_command **command,
	t_program *minishell, t_pipeline *pipeline)
{
	if (token->type == TKN_WORD)
		return (parser_word(token, *command));
	if (token->type == TKN_IN || token->type == TKN_OUT
		|| token->type == TKN_RDA || token->type == TKN_RDH)
		return (parser_redirection(token, *command, minishell));
	if (token->type == TKN_ENV)
		return (parser_env(token, *command, minishell));
	if (token->type == TKN_WILDCARD)
		return (parser_wildcard(token, *command));
	if (token->type == TKN_STATUS)
		return (parser_status(token, minishell));
	if (token->type == TKN_PIPE)
		return (parser_pipe(token, command, pipeline));
	if (token->type == TKN_AND || token->type == TKN_OR)
		return (parser_logical(token, command, pipeline));
	return (token->next);
}

t_token	*parser_word(t_token *token, t_command *command)
{
	if (!token->value || !token->value[0])
		return (token->next);
	if (!parser_argument(command, token->value))
		ft_error("Parser: Failed to add argument\n");
	if (command->arguments[0] && parser_builtin(command->arguments[0]))
		command->is_builtin = 1;
	return (token->next);
}

t_token	*parser_pipe(t_token *token, t_command **command, t_pipeline *pipeline)
{
	t_command	*new;
	t_command	**new_commands;
	int			count;

	new = create_command();
	if (*command)
		(*command)->next = new;
	pipeline->cmd_count++;
	new_commands = malloc(sizeof(t_command *) * pipeline->cmd_count);
	if (!new_commands)
		ft_error("Parser: Pipe allocation failed\n");
	count = 0;
	while (pipeline->commands && count < pipeline->cmd_count - 1)
	{
		new_commands[count] = pipeline->commands[count];
		count++;
	}
	free(pipeline->commands);
	new_commands[count] = new;
	pipeline->commands = new_commands;
	*command = new;
	return (token->next);
}

int	parser_sequence(t_token *token, t_program *minishell)
{
	t_token	*current;
	t_token	*previous;

	current = token;
	previous = NULL;
	if (!token || ((!token->value || !*token->value) && !token->next))
		return (0);
	while (current)
	{
		if (!sequence_heredoc(current, minishell))
			return (0);
		if (!sequence_operators(current, previous, minishell))
			return (0);
		if (!sequence_redirect(current, minishell))
			return (0);
		if (!sequence_pipes(current, minishell))
			return (0);
		previous = current;
		current = current->next;
	}
	return (1);
}
