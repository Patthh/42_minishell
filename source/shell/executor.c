#include "../../include/minishell.h"

// static char *find_command_path(char *cmd, char **envp)
// {
//     char    **paths;
//     char    *path;
//     char    *full_path;
//     int     i;
//     if (!cmd || !envp)
//         return (NULL);
//     if (access(cmd, X_OK) == 0)
//         return (ft_strdup(cmd));
//     i = 0;
//     while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
//         i++;
//     if (!envp[i])
//         return (NULL);
//     paths = ft_split(envp[i] + 5, ':');
//     i = 0;
//     while (paths[i])
//     {
//         path = ft_strjoin(paths[i], "/");
//         full_path = ft_strjoin(path, cmd);
//         free(path);
//         if (access(full_path, X_OK) == 0)
//         {
//             while (paths[i])
//                 free(paths[i++]);
//             free(paths);
//             return (full_path);
//         }
//         free(full_path);
//         i++;
//     }
//     while (paths[i])
//         free(paths[i++]);
//     free(paths);
//     return (NULL);
// }
static char	**get_paths_from_env(char **envp)
{
	int		i;
	char	**paths;

	if (!envp)
		return (NULL);
	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5))
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

static char	*get_full_path(char *dir, char *cmd)
{
	char	*path;
	char	*full_path;

	if (!dir || !cmd)
		return (NULL);
	path = ft_strjoin(dir, "/");
	if (!path)
		return (NULL);
	full_path = ft_strjoin(path, cmd);
	free(path);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

static char	*find_command_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = get_paths_from_env(envp);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = get_full_path(paths[i], cmd);
		if (full_path)
		{
			free_paths(paths);
			return (full_path);
		}
		i++;
	}
	free_paths(paths);
	return (NULL);
}

// static void	execute_external(t_command *command, t_program *minishell)
// {
// 	char	*cmd_path;
// 	pid_t	pid;
// 	int		status;
// 	if (!command->arguments[0])
// 		return ;
// 	cmd_path = find_command_path(command->arguments[0], minishell->envp);
// 	if (!cmd_path)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(command->arguments[0], 2);
// 		ft_putstr_fd(": command not found\n", 2);
// 		minishell->status = 127;
// 		return ;
// 	}
// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		free(cmd_path);
// 		ft_putstr_fd("minishell: fork failed\n", 2);
// 		minishell->status = 1;
// 		return ;
// 	}
// 	if (pid == 0)
// 	{
// 		if (execve(cmd_path, command->arguments, minishell->envp) == -1)
// 		{
// 			ft_putstr_fd("minishell: ", 2);
// 			ft_putstr_fd(command->arguments[0], 2);
// 			ft_putstr_fd(": ", 2);
// 			ft_putstr_fd(strerror(errno), 2);
// 			ft_putstr_fd("\n", 2);
// 			free(cmd_path);
// 			exit(errno);
// 		}
// 	}
// 	else
// 	{
// 		waitpid(pid, &status, 0);
// 		if (WIFEXITED(status))
// 			minishell->status = WEXITSTATUS(status);
// 		else if (WIFSIGNALED(status))
// 			minishell->status = 128 + WTERMSIG(status);
// 	}
// 	free(cmd_path);
// }
static void	handle_execution_error(t_command *command, t_program *minishell,
		char *cmd_path, int error_type)
{
	if (error_type == 1) // Command not found
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command->arguments[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		minishell->status = 127;
	}
	else if (error_type == 2) // Fork failure
	{
		ft_putstr_fd("minishell: fork failed\n", 2);
		minishell->status = 1;
	}
	free(cmd_path);
}

static void	handle_execution_status(pid_t pid, t_program *minishell)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		minishell->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		minishell->status = 128 + WTERMSIG(status);
}

static void	execute_in_child(char *cmd_path, t_command *command,
		t_program *minishell)
{
	if (execve(cmd_path, command->arguments, minishell->envp) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command->arguments[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		free(cmd_path);
		exit(errno);
	}
}

static void	fork_and_execute(char *cmd_path, t_command *command,
		t_program *minishell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		handle_execution_error(command, minishell, cmd_path, 2);
		return ;
	}
	if (pid == 0)
		execute_in_child(cmd_path, command, minishell);
	else
		handle_execution_status(pid, minishell);
	free(cmd_path);
}

static void	execute_external(t_command *command, t_program *minishell)
{
	char	*cmd_path;

	if (!command->arguments[0])
		return ;
	cmd_path = find_command_path(command->arguments[0], minishell->envp);
	if (!cmd_path)
	{
		handle_execution_error(command, minishell, NULL, 1);
		return ;
	}
	fork_and_execute(cmd_path, command, minishell);
}

void	execute_pipeline(t_pipeline *pipeline, t_program *minishell)
{
	t_command	*command;
	int			i;

	i = 0;
	if (pipeline == NULL)
		return ;
	while (i < pipeline->cmd_count)
	{
		command = pipeline->commands[i];
		execute_command(command, minishell);
		i++;
	}
}

void	execute_command(t_command *command, t_program *minishell)
{
	if (command == NULL || command->arguments == NULL)
		return ;
	if (command->is_builtin)
		execute_builtin(command, minishell);
	else
		execute_external(command, minishell);
}

void	execute_builtin(t_command *command, t_program *minishell)
{
	if (ft_strcmp(command->arguments[0], "echo") == 0)
		ft_echo(command, minishell);
	// else if (ft_strcmp(command->arguments[0], "cd") == 0)
	// 	ft_cd(minishell);
	else if (ft_strcmp(command->arguments[0], "pwd") == 0)
		ft_pwd(minishell);
	else if (ft_strcmp(command->arguments[0], "export") == 0)
		ft_export(command, minishell);
	else if (ft_strcmp(command->arguments[0], "unset") == 0)
		ft_unset(command, minishell);
	else if (ft_strcmp(command->arguments[0], "env") == 0)
		ft_env(minishell);
	else if (ft_strcmp(command->arguments[0], "exit") == 0)
		ft_exit(command, minishell);
}
