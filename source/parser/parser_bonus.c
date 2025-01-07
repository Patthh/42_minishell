#include "../../include/minishell.h"

// t_token	*parser_and(t_token *token, t_command **command, t_pipeline *pipeline)
// {
// 	t_command	*new;
// 	t_command	**new_commands;
// 	int			count;

// 	new = create_command();
// 	if (*command)
// 		(*command)->next = new;
// 	pipeline->cmd_count++;
// 	new_commands = malloc(sizeof(t_command *) * pipeline->cmd_count);
// 	if (!new_commands)
// 		ft_error("Parser: AND allocation failed\n");
// 	count = 0;
// 	while (pipeline->commands && count < pipeline->cmd_count - 1)
// 	{
// 		new_commands[count] = pipeline->commands[count];
// 		count++;
// 	}
// 	free(pipeline->commands);
// 	new_commands[count] = new;
// 	pipeline->commands = new_commands;
// 	*command = new;
// 	return (token->next);
// }

// t_token	*parser_or(t_token *token, t_command **command, t_pipeline *pipeline)
// {
// 	t_command	*new;
// 	t_command	**new_commands;
// 	int			count;

// 	new = create_command();
// 	if (*command)
// 		(*command)->next = new;
// 	pipeline->cmd_count++;
// 	new_commands = malloc(sizeof(t_command *) * pipeline->cmd_count);
// 	if (!new_commands)
// 		ft_error("Parser: OR allocation failed\n");
// 	count = 0;
// 	while (pipeline->commands && count < pipeline->cmd_count - 1)
// 	{
// 		new_commands[count] = pipeline->commands[count];
// 		count++;
// 	}
// 	free(pipeline->commands);
// 	new_commands[count] = new;
// 	pipeline->commands = new_commands;
// 	*command = new;
// 	return (token->next);
// }

t_token	*parser_wildcard(t_token *token, t_command *command)
{
	if (!token || !command)
		return (NULL);
	if (!parser_argument(command, token->value))
		ft_error("Parser: failed to add wildcard argument\n");
	return (token->next);
}
