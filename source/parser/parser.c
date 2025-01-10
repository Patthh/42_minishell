#include "../../include/minishell.h"

t_pipeline	*create_pipeline(void)
{
	t_pipeline	*pipeline;

	pipeline = malloc(sizeof(t_pipeline));
	if (!pipeline)
		ft_error("Parser: Pipeline Memory Allocation Failed");
	pipeline->commands = malloc(sizeof(t_command *));
	if (!pipeline->commands)
		ft_error("Parser: Commands Memory Allocation Failed");
	pipeline->cmd_count = 0;
	pipeline->commands[0] = NULL;
	return (pipeline);
}

t_command	*create_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (!command)
		ft_error("Parser: Command Memory Allocaiton Failed");
	command->arguments = NULL;
	command->input = NULL;
	command->output = NULL;
	command->append = NULL;
	command->heredoc = NULL;
	command->fd_in = STDIN_FILENO;
	command->fd_out = STDOUT_FILENO;
	command->is_builtin = 0;
	command->exit_status = 0;
	command->logical = LOG_NONE;
	command->next = NULL;
	return (command);
}

t_redirection	*create_redirection(const char *type, const char *filename, int quoted)
{
	t_redirection	*redirection;

	redirection = malloc(sizeof(t_redirection));
	if (!redirection)
		ft_error("Parser: Redirection allocation Failed");
	redirection->type = ft_strdup(type);
	redirection->filename = ft_strdup(filename);
	redirection->quoted = quoted;
	redirection->content = NULL;
	redirection->next = NULL;
	return (redirection);
}

// t_group	*create_group(void)
// {
// 	t_group	*group;

// 	group = malloc(sizeof(t_group));
// 	if (!group)
// 		ft_error("Parser: Group Memory Allocation Failed");
// 	group->type = GROUP_COMMAND;
// 	group->content.command = NULL;
// 	group->logical = LOG_NONE;
// 	group->exit_status = 0;
// 	group->next = NULL;
// 	return (group);
// }


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

	if (!parser_sequence(tokens, minishell))
		return (NULL);
	pipeline = create_pipeline();
	command = create_command();
	pipeline->commands[0] = command;
	pipeline->cmd_count = 1;
	token = tokens;
	while (token)
	{
		token = parser_token(token, &command, minishell, pipeline);
		if (token && token->type == TKN_PIPE)
			command = command->next;
	}
	return (pipeline);
}
