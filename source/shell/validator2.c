#include "../../include/minishell.h"

static int	validate_special(char *arg, t_program *minishell)
{
	if (arg[0] == '{')
	{
		error_unexpected_eof(minishell);
		return (0);
	}
	if (arg[0] == '}')
	{
		error_brace("}", minishell);
		return (0);
	}
	return (1);
}

static int	is_path_command(char *arg)
{
	return (arg[0] == '/' || (arg[0] == '.' && arg[1] == '/')
		|| (arg[0] == '.' && arg[1] == '.' && arg[2] == '/'));
}

// checks if path exists
// check if it's a regular file
// check if it's a directory
static int	validate_path(char *path, t_program *minishell)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
	{
		error_file_not_found_127(path, minishell);
		return (0);
	}
	if (S_ISREG(path_stat.st_mode))
	{
		if (access(path, X_OK) == -1)
		{
			error_permission(path, minishell);
			return (0);
		}
		return (1);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		error_directory(path, minishell);
		return (0);
	}
	error_command(path, minishell);
	return (0);
}

static int	validate_command_name(char *arg, t_program *minishell)
{
	if (!valid_cmd_name(arg))
	{
		if (ft_strcmp(arg, "$?") == 0)
			error_command("$?", minishell);
		else if (arg[0] == '(' || arg[0] == ')'
			|| arg[0] == '{' || arg[0] == '}')
			error_syntax(arg, minishell);
		else
			error_command(arg, minishell);
		return (0);
	}
	return (1);
}

int	validate_content(t_command *command, t_program *minishell)
{
	char	*argument;

	argument = command->arguments[0];
	if (!validate_special(argument, minishell))
		return (0);
	if (is_path_command(argument))
		return (validate_path(argument, minishell));
	return (validate_command_name(argument, minishell));
}
