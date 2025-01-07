#include "../../include/minishell.h"

// static char	*expand_path(const char *original_path, t_program *minishell)
// {
// 	char	*home_path;
// 	char	*expanded_path;
// 	char	*oldpwd;
// 	if (!original_path)
// 		return (NULL);
// 	// printf("Expanding path: %s\n", original_path);
// 	if (ft_strcmp(original_path, "-") == 0)
// 	{
// 		oldpwd = env_value(minishell, "OLDPWD");
// 		if (!oldpwd)
// 		{
// 			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
// 			return (NULL);
// 		}
// 		printf("%s\n", oldpwd);
// 		return (ft_strdup(oldpwd));
// 	}
// 	if (original_path[0] == '~')
// 	{
// 		home_path = env_value(minishell, "HOME");
// 		if (!home_path)
// 		{
// 			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
// 			return (NULL);
// 		}
// 		if (original_path[1] == '\0') // Just ~
// 			return (ft_strdup(home_path));
// 		else if (original_path[1] == '/') // ~/something
// 		{
// 			expanded_path = ft_strjoin(home_path, original_path + 1);
// 			printf("Expanded ~/ path to: %s\n", expanded_path);
// 			return (expanded_path);
// 		}
// 	}
// 	return (ft_strdup(original_path));
// }
// int	ft_cd(t_command *command, t_program *minishell)
// {
// 	char *path;
// 	char *expanded_path;
// 	char cwd[PATH_MAX];
// 	// printf("\n=== CD Command Debug ===\n");
// 	// printf("Command received: %s\n", command->arguments[0]);
// 	// printf("Argument: %s\n",
// 			command->arguments[1] ? command->arguments[1] : "none");
// 	if (!command->arguments[1])
// 	{
// 		path = env_value(minishell, "HOME");
// 		if (!path)
// 		{
// 			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
// 			minishell->status = 1;
// 			return (1);
// 		}
// 		expanded_path = ft_strdup(path);
// 	}
// 	else
// 	{
// 		expanded_path = expand_path(command->arguments[1], minishell);
// 		if (!expanded_path)
// 		{
// 			minishell->status = 1;
// 			return (1);
// 		}
// 	}
// 	// printf("Attempting to cd to: %s\n", expanded_path);
// 	if (chdir(expanded_path) == -1)
// 	{
// 		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
// 		ft_putstr_fd(expanded_path, STDERR_FILENO);
// 		ft_putstr_fd(": ", STDERR_FILENO);
// 		ft_putstr_fd(strerror(errno), STDERR_FILENO);
// 		ft_putstr_fd("\n", STDERR_FILENO);
// 		free(expanded_path);
// 		minishell->status = 1;
// 		return (1);
// 	}
// 	// if (getcwd(cwd, sizeof(cwd)) != NULL)
// 	// 	printf("Current directory after cd: %s\n", cwd);
// 	free(expanded_path);
// 	minishell->status = 0;
// 	return (0);
// }
static char	*handle_oldpwd_path(t_program *minishell)
{
	char	*oldpwd;

	oldpwd = env_value(minishell, "OLDPWD");
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
		return (NULL);
	}
	printf("%s\n", oldpwd);
	return (ft_strdup(oldpwd));
}

static char	*handle_home_expansion(const char *original_path,
		t_program *minishell)
{
	char	*home_path;
	char	*expanded_path;

	home_path = env_value(minishell, "HOME");
	if (!home_path)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	if (original_path[1] == '\0')
		return (ft_strdup(home_path));
	expanded_path = ft_strjoin(home_path, original_path + 1);
	return (expanded_path);
}

static char	*expand_path(const char *original_path, t_program *minishell)
{
	if (!original_path)
		return (NULL);
	if (ft_strcmp(original_path, "-") == 0)
		return (handle_oldpwd_path(minishell));
	if (original_path[0] == '~')
		return (handle_home_expansion(original_path, minishell));
	return (ft_strdup(original_path));
}

static int	handle_cd_error(char *expanded_path, t_program *minishell)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(expanded_path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(expanded_path);
	minishell->status = 1;
	return (1);
}

int	ft_cd(t_command *command, t_program *minishell)
{
	char	*path;
	char	*expanded_path;

	path = env_value(minishell, "HOME");
	if (!command->arguments[1])
	{
		if (!(path))
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (minishell->status = 1, 1);
		}
		expanded_path = ft_strdup(path);
	}
	else
		expanded_path = expand_path(command->arguments[1], minishell);
	if (!expanded_path)
		return (minishell->status = 1, 1);
	if (chdir(expanded_path) == -1)
		return (handle_cd_error(expanded_path, minishell));
	free(expanded_path);
	return (minishell->status = 0, 0);
}
