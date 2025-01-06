#include "../../include/minishell.h"

#include "../../include/minishell.h"

// int ft_cd(t_command *command, t_program *minishell)
// {
//     char *path;
//     // printf("ft_cd: Starting cd command\n");
//     // printf("ft_cd: Number of arguments: %d\n",
		// command ? (command->arguments ? 2 : 0) : 0);

//     if (!command->arguments[1] || ft_strcmp(command->arguments[1], "~") == 0)
//     {
//         // printf("ft_cd: No argument or '~' provided,
		// trying to get HOME\n");
//         path = env_value(minishell, "HOME");
//         if (!path)
//         {
//             // printf("ft_cd: HOME environment variable not found\n");
//             ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
//             minishell->status = 1;
//             return (1);
//         }
//         printf("ft_cd: HOME path = '%s'\n", path);
//     }
//     if (!command->arguments[1] || ft_strcmp(command->arguments[1], "-") == 0)
//     {
//         // printf("ft_cd: No argument or '~' provided,
		// trying to get HOME\n");
//         path = env_value(minishell, "OLDPWD");
//         // if (!path)
//         // {
//         //     // printf("ft_cd: HOME environment variable not found\n");
//         //     // ft_putstr_fd("minishell: cd: HOME not set\n",
		// STDERR_FILENO);
//         //     minishell->status = 1;
//         //     return (1);
//         // }
//         printf("ft_cd: PREVIOUS path = '%s'\n", path);
//     }
//     else
//     {
//         path = command->arguments[1];
//         printf("ft_cd: Using provided path = '%s'\n", path);
//     }
//     printf("ft_cd: Attempting to change directory to '%s'\n", path);
//     if (chdir(path) == -1)
//     {
//         printf("ft_cd: chdir failed with errno = %d\n", errno);
//         ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
//         ft_putstr_fd(path, STDERR_FILENO);
//         ft_putstr_fd(": ", STDERR_FILENO);
//         ft_putstr_fd(strerror(errno), STDERR_FILENO);
//         ft_putstr_fd("\n", STDERR_FILENO);
//         minishell->status = 1;
//         return (1);
//     }
//     printf("ft_cd: Successfully changed directory to '%s'\n", path);
//     char cwd[PATH_MAX];
//     if (getcwd(cwd, sizeof(cwd)) != NULL)
//         printf("ft_cd: Current working directory is: %s\n", cwd);
//     else
//         printf("ft_cd: Failed to get current working directory\n");
//     minishell->status = 0;
//     return (0);
// }
static char	*expand_path(const char *original_path, t_program *minishell)
{
	char	*home_path;
	char	*expanded_path;
	char	*oldpwd;

	if (!original_path)
		return (NULL);
	printf("Expanding path: %s\n", original_path);
	if (ft_strcmp(original_path, "-") == 0)
	{
		oldpwd = env_value(minishell, "OLDPWD");
		if (!oldpwd)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", STDERR_FILENO);
			return (NULL);
		}
		printf("%s\n", oldpwd);
		return (ft_strdup(oldpwd));
	}
	// Handle path starting with ~/ or just ~
	if (original_path[0] == '~')
	{
		home_path = env_value(minishell, "HOME");
		if (!home_path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
		if (original_path[1] == '\0') // Just ~
			return (ft_strdup(home_path));
		else if (original_path[1] == '/') // ~/something
		{
			expanded_path = ft_strjoin(home_path, original_path + 1);
			printf("Expanded ~/ path to: %s\n", expanded_path);
			return (expanded_path);
		}
	}
	return (ft_strdup(original_path));
}

int	ft_cd(t_command *command, t_program *minishell)
{
	char *path;
	char *expanded_path;
	char cwd[PATH_MAX];

	printf("\n=== CD Command Debug ===\n");
	printf("Command received: %s\n", command->arguments[0]);
	printf("Argument: %s\n",
			command->arguments[1] ? command->arguments[1] : "none");

	if (!command->arguments[1])
	{
		path = env_value(minishell, "HOME");
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			minishell->status = 1;
			return (1);
		}
		expanded_path = ft_strdup(path);
	}
	else
	{
		expanded_path = expand_path(command->arguments[1], minishell);
		if (!expanded_path)
		{
			minishell->status = 1;
			return (1);
		}
	}

	printf("Attempting to cd to: %s\n", expanded_path);

	if (chdir(expanded_path) == -1)
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

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("Current directory after cd: %s\n", cwd);

	free(expanded_path);
	minishell->status = 0;
	return (0);
}

// static void	update_cd(t_program *minishell)
// {
// 	char	*cwd;
// 	char	*old;

// 	cwd = getcwd(NULL, 0);
// 	if (!cwd)
// 	{
// 		ft_putstr_fd("cd: error retrieving current driectory\n", STDERR_FILENO);
// 		return ;
// 	}
// 	old = getenv(minishell, "PWD");
// }

// // chdir - change working directory
// // strerror - return string describing error number
// int	ft_cd(t_command *command, t_program *minishell)
// {
// 	char	*directory;

// 	if (!command->arguments[1])
// 	{
// 		ft_putstr_fd("cd: missing directory argument\n", STDERR_FILENO);
// 		minishell->status = 1;
// 		return (1);
// 	}
// 	directory = command->arguments[1];
// 	if (chdir(directory) == -1)
// 	{
// 		ft_putstr_fd("cd: ", STDERR_FILENO);
// 		ft_putstr_fd(directory, STDERR_FILENO);
// 		ft_putstr_fd(": ", STDERR_FILENO);
// 		ft_putstr_fd(strerror(errno), STDERR_FILENO);
// 		ft_putstr_fd("\n", STDERR_FILENO);
// 		minishell->status = 1;
// 		return (1);
// 	}
// 	update_cd(minishell);
// 	minishell->status = 0;
// 	return (0);
// }
