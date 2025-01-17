#include "../../include/minishell.h"

int	valid_cmd_name(const char *name)
{
	return (name && *name && *name != '{' && *name != '}');
}

static int	validate_empty(t_command *command, t_program *minishell)
{
	if (!command)
	{
		minishell->status = 0;
		return (0);
	}
	if (!command->arguments || !command->arguments[0])
	{
		if (!command->arguments)
			error_syntax("", minishell);
		else if (!command->arguments[0][0])
		{
			minishell->status = 0;
			return (0);
		}
		else
			error_syntax("newline", minishell);
		return (0);
	}
	return (1);
}

static int	validate_content(t_command *command, t_program *minishell)
{
	if (command->arguments[0][0] == '{')
	{
		error_unexpected_eof(minishell);
		return (0);
	}
	if (command->arguments[0][0] == '}')
	{
		error_brace("}", minishell);
		return (0);
	}
	if (!valid_cmd_name(command->arguments[0]))
	{
		if (ft_strcmp(command->arguments[0], "$?") == 0)
			error_command("$?", minishell);
		else
			error_command(command->arguments[0], minishell);
		return (0);
	}
	return (1);
}

int	validate_pipeline(t_pipeline *pipeline, t_program *minishell)
{
	int	i;

	if (!pipeline || pipeline->cmd_count == 0 || !pipeline->commands)
	{
		minishell->status = 0;
		return (1);
	}
	i = 0;
	while (i < pipeline->cmd_count)
	{
		if (!pipeline->commands[i])
		{
			i++;
			continue ;
		}
		if (!validate_empty(pipeline->commands[i], minishell)
			|| (!validate_content(pipeline->commands[i], minishell)))
			return (0);
		i++;
	}
	return (1);
}
