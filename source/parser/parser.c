#include "../../include/minishell.h"

t_pipeline	*create_pipeline(void)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		ft_error("Parser: Pipeline Memory Allocation Failed\n");
	pipeline->commands = NULL;
	pipeline->cmd_count = 0;
	return (pipeline);
}

t_command	*create_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		ft_error("Parser: Command Memory Allocaiton Failed.\n");
	command->arguments = NULL;
	command->input = NULL;
	command->output = NULL;
	command->fd_in = STDIN_FILENO;
	command->fd_out = STDOUT_FILENO;
	command->is_builtin = 0;
	command->next = NULL;
	return (command);
}

t_redirection	*create_redirection(const char *type, const char *filename)
{
	t_redirection	*redirection;

	redirection = malloc(sizeof(t_redirection));
	if (!redirection)
		ft_error("Parser: Redirection allocation Failed\n");
	redirection->type = ft_strdup(type);
	redirection->filename = ft_strdup(filename);
	redirection->next = NULL;
	return (redirection);
}

// parse token and build commands
// update command and pipeline as needed
t_token	*parse_token(t_token *token, t_command *command, t_program *minihell, t_pipeline *pipeline)
{
	if (token->type == TKN_WORD)
		return (parse_word(token, command));
	if (token->type == TKN_PIPE)
		return (parse_pipe(token, command, pipeline));
	if (token->type == TKN_IN || token->type == TKN_OUT || token->type == TKN_RDA || token->type == TKN_RDH)
		return (parse_redirection(token, command));
	return (token->next);
}


// Preparation
// Verify input token are valid
// Prepare data structures for parsing
// Create pipeline to hold commands
// Prepare to track current command being built
t_pipeline	*parser(t_token *tokens, t_program *minishell)
{
	t_pipeline	*pipeline;
	t_command	*command;
	t_token		*token;

	pipeline = create_pipeline();

	// init first command
	command = create_command();
	pipeline->commands = command;
	pipeline->cmd_count = 1;

	// parse tokens
	token = tokens;
	while (token)
	{
		token = parse_token(token, command, minishell, pipeline);
		if (!token)
		{
			ft_error("Parser: Failed to parse token.\n");
			free_pipeline (pipeline);
			return (NULL);
		}
	}
	return (pipeline);
}
