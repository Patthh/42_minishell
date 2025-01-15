#include "../../include/minishell.h"

// access() checks whether the calling process can access the file pathname.
// If pathname is a symbolic link, it is dereferenced.
// helper functions in utils/utils_cd.c

void	cd_error(char *path, char *message)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	if (path)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(message, STDERR_FILENO);
}

static int	chdir_error(char *target_path)
{
	if (access(target_path, F_OK) == -1)
		cd_error(target_path, "No such file or directory");
	else if (access(target_path, X_OK) == -1)
		cd_error(target_path, "permission denied");
	else
		cd_error(target_path, "not a directory");
	return (1);
}

static int	validate_arguments(t_command *command)
{
	if (command->arguments && command->arguments[1] && command->arguments[2])
	{
		cd_error(NULL, "too many arguments");
		return (0);
	}
	return (1);
}

int	ft_cd(t_command *command, t_program *minishell)
{
	char	*target_path;
	int		ret;

	if (!validate_arguments(command))
	{
		minishell->status = 1;
		return (1);
	}
	target_path = get_target(command, minishell);
	if (!target_path)
	{
		minishell->status = 1;
		return (1);
	}
	if (chdir(target_path) == -1)
	{
		ret = chdir_error(target_path);
		free(target_path);
		minishell->status = 1;
		return (ret);
	}
	ret = update_pwd(minishell);
	free(target_path);
	minishell->status = (ret != 0);
	return (ret);
}
