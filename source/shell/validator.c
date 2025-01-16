#include "../../include/minishell.h"

int	valid_cmd_name(const char *name)
{
	return (name && *name && *name != '{' && *name != '}');
}

int	validate_command(t_command *command, t_program *minishell)
{
	if (!command->arguments || !command->arguments[0])
	{
		error_newline(minishell);
		return 0;
	}
	if (command->arguments[0][0] == '{')
	{
		error_unexpected_eof(minishell);
		return 0;
	}
	if (command->arguments[0][0] == '}')
	{
		error_brace("}", minishell);
		return 0;
	}
	if (!valid_cmd_name(command->arguments[0]))
	{
		error_command(command->arguments[0], minishell);
		return 0;
	}
	return 1;
}

int validate_pipeline(t_pipeline *pipeline, t_program *minishell)
{
	int i;

	if (!pipeline || pipeline->cmd_count == 0)
	{
		error_newline(minishell);
		return 0;
	}
	i = 0;
	while (i < pipeline->cmd_count)
	{
		if (!pipeline->commands[i])
			continue;
		if (!validate_command(pipeline->commands[i], minishell))
			return 0;
		i++;
	}
	return 1;
}


