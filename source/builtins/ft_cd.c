#include "../../include/minishell.h"

//extracts value of an env
static char	*path_env(t_program *minishell, const char *env_var, char *error)
{
	char	*path;

	path = env_value(minishell, env_var);
	if (!path)
	{
		ft_putstr_fd(error, STDERR_FILENO);
		return (NULL);
	}
	if (ft_strcmp(env_var, "OLDPWD") == 0)
	{
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	return (path);
}

// expands a path with a tilde (~) to its absolute path
static char	*path_tilde(char *path, t_program *minishell)
{
	char	*home;

	if (path[0] != '~')
		return (ft_strdup(path));
	home = path_env(minishell, "HOME", "minishell: cd: HOME not set\n");
	if (!home)
		return (NULL);
	if (path[1] == '\0')
		return (ft_strdup(home));
	else if (path[1] == '/')
		return (ft_strjoin(home, path + 1));
	return (ft_strdup(path));
}

// get current working directory
// change directory
// get new working directory
// update OLDPWD and PWD in environment
static int	path_update(char *path, t_program *minishell)
{
	char	old[PATH_MAX];
	char	new[PATH_MAX];
	if (getcwd(old, PATH_MAX) == NULL)
	{
		ft_putstr_fd("minishell: cd: error getting current directory\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return (-1);
	}
	if (getcwd(new, PATH_MAX) == NULL)
	{
		ft_putstr_fd("minishell: cd: error getting new directory\n", STDERR_FILENO);
		return (1);
	}
	add_env(minishell, "OLDPWD", old);
	add_env(minishell, "PWD", new);
	return (0);
}

static int	cd_valid(t_command *command, t_program *minishell)
{
	if (!command->arguments[1])
		return (1);
	if (command->arguments[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		minishell->status = 1;
		return (1);
	}
	return (0);
}

int ft_cd(t_command *command, t_program *minishell)
{
	char	*target;
	char	*expanded;

	target = NULL;
	expanded = NULL;
	if (cd_valid(command, minishell))
		return (1);
	if (ft_strcmp(command->arguments[1], "-") == 0)
		target = path_env(minishell, "OLDPWD", "minishell: cd: OLDPWD not set\n");
	else
	{
		expanded = path_tilde(command->arguments[1], minishell);
		target = expanded;
	}
	if (path_update(target, minishell) != 0)
	{
		free (expanded);
		minishell->status = 1;
		return (1);
	}
	free(expanded);
	minishell->status = 0;
	return (0);
}


// // int ft_cd(t_command *command, t_program *minishell)
// // {
// //     char *path;
// //     // printf("ft_cd: Starting cd command\n");
// //     // printf("ft_cd: Number of arguments: %d\n",
// 		// command ? (command->arguments ? 2 : 0) : 0);

// //     if (!command->arguments[1] || ft_strcmp(command->arguments[1], "~") == 0)
// //     {
// //         // printf("ft_cd: No argument or '~' provided,
// 		// trying to get HOME\n");
// //         path = env_value(minishell, "HOME");
// //         if (!path)
// //         {
// //             // printf("ft_cd: HOME environment variable not found\n");
// //             ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
// //             minishell->status = 1;
// //             return (1);
// //         }
// //         printf("ft_cd: HOME path = '%s'\n", path);
// //     }
// //     if (!command->arguments[1] || ft_strcmp(command->arguments[1], "-") == 0)
// //     {
// //         // printf("ft_cd: No argument or '~' provided,
// 		// trying to get HOME\n");
// //         path = env_value(minishell, "OLDPWD");
// //         // if (!path)
// //         // {
// //         //     // printf("ft_cd: HOME environment variable not found\n");
// //         //     // ft_putstr_fd("minishell: cd: HOME not set\n",
// 		// STDERR_FILENO);
// //         //     minishell->status = 1;
// //         //     return (1);
// //         // }
// //         printf("ft_cd: PREVIOUS path = '%s'\n", path);
// //     }
// //     else
// //     {
// //         path = command->arguments[1];
// //         printf("ft_cd: Using provided path = '%s'\n", path);
// //     }
// //     printf("ft_cd: Attempting to change directory to '%s'\n", path);
// //     if (chdir(path) == -1)
// //     {
// //         printf("ft_cd: chdir failed with errno = %d\n", errno);
// //         ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
// //         ft_putstr_fd(path, STDERR_FILENO);
// //         ft_putstr_fd(": ", STDERR_FILENO);
// //         ft_putstr_fd(strerror(errno), STDERR_FILENO);
// //         ft_putstr_fd("\n", STDERR_FILENO);
// //         minishell->status = 1;
// //         return (1);
// //     }
// //     printf("ft_cd: Successfully changed directory to '%s'\n", path);
// //     char cwd[PATH_MAX];
// //     if (getcwd(cwd, sizeof(cwd)) != NULL)
// //         printf("ft_cd: Current working directory is: %s\n", cwd);
// //     else
// //         printf("ft_cd: Failed to get current working directory\n");
// //     minishell->status = 0;
// //     return (0);
// // }
// static char	*expand_path(const char *original_path, t_program *minishell)
// {
// 	char	*home_path;
// 	char	*expanded_path;
// 	char	*oldpwd;

// 	if (!original_path)
// 		return (NULL);
// 	printf("Expanding path: %s\n", original_path);
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
// 	// Handle path starting with ~/ or just ~
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

// 	printf("\n=== CD Command Debug ===\n");
// 	printf("Command received: %s\n", command->arguments[0]);
// 	printf("Argument: %s\n",
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

// 	printf("Attempting to cd to: %s\n", expanded_path);

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

// 	if (getcwd(cwd, sizeof(cwd)) != NULL)
// 		printf("Current directory after cd: %s\n", cwd);

// 	free(expanded_path);
// 	minishell->status = 0;
// 	return (0);
// }
