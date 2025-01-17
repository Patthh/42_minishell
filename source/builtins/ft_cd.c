#include "../../include/minishell.h"

// access() checks whether the calling process can access the file pathname.
// If pathname is a symbolic link, it is dereferenced.
// helper functions in utils/utils_cd.c
static int	chdir_error(char *target_path, t_program *minishell)
{
	struct stat	path_stat;

	if (stat(target_path, &path_stat) == -1)
	{
		if (access(target_path, F_OK) == -1)
			error_not_found(target_path, minishell);
		else
			error_permission(target_path, minishell);
	}
	else
	{
		if (!S_ISDIR(path_stat.st_mode))
			error_directory(target_path, minishell);
		else if (access(target_path, X_OK) == -1)
			error_permission(target_path, minishell);
	}
	return (1);
}

static int	validate_arguments(t_command *command, t_program *minishell)
{
	if (command->arguments && command->arguments[1] && command->arguments[2])
	{
		error_arguments("cd", minishell);
		return (0);
	}
	return (1);
}

static int	validate_path(char *target_path, t_program *minishell)
{
	struct stat	path_stat;

	if (stat(target_path, &path_stat) == -1)
	{
		if (access(target_path, F_OK) == -1)
			error_not_found(target_path, minishell);
		else
			error_permission(target_path, minishell);
		return (0);
	}
	if (!S_ISDIR(path_stat.st_mode))
	{
		error_directory(target_path, minishell);
		return (0);
	}
	if (access(target_path, X_OK) == -1)
	{
		error_permission(target_path, minishell);
		return (0);
	}
	return (1);
}

int	ft_cd(t_command *command, t_program *minishell)
{
	char	*target_path;
	int		ret;

	if (!validate_arguments(command, minishell))
		return (1);
	target_path = get_target(command, minishell);
	if (!target_path)
	{
		minishell->status = 1;
		return (1);
	}
	if (!validate_path(target_path, minishell))
	{
		free(target_path);
		return (1);
	}
	if (chdir(target_path) == -1)
	{
		ret = chdir_error(target_path, minishell);
		free(target_path);
		return (ret);
	}
	ret = update_pwd(minishell);
	free(target_path);
	return (ret);
}
