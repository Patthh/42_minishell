#include "../../include/minishell.h"

static void	execute_in_child(char *cmd_path, t_command *command,
				t_program *minishell);

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

// static void	execute_in_child(char *cmd_path, t_command *command,
// 		t_program *minishell)
// {
// 	if (execve(cmd_path, command->arguments, minishell->envp) == -1)
// 	{
// 		ft_putstr_fd("minishell: ", 2);
// 		ft_putstr_fd(command->arguments[0], 2);
// 		ft_putstr_fd(": ", 2);
// 		ft_putstr_fd(strerror(errno), 2);
// 		ft_putstr_fd("\n", 2);
// 		free(cmd_path);
// 		exit(errno);
// 	}
// }

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

// void	execute_command(t_command *command, t_program *minishell)
// {
// 	if (command == NULL || command->arguments == NULL)
// 		return ;
// 	if (command->is_builtin)
// 		execute_builtin(command, minishell);
// 	else
// 		execute_external(command, minishell);
// }

void	execute_builtin(t_command *command, t_program *minishell)
{
	if (ft_strcmp(command->arguments[0], "echo") == 0)
		ft_echo(command, minishell);
	else if (ft_strcmp(command->arguments[0], "cd") == 0)
		ft_cd(command, minishell);
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
/// @brief PIPE HERE
/// @param pipeline
/// @param pipe_fds
static void	setup_pipes(t_pipeline *pipeline, int **pipe_fds)
{
	int	i;

	for (i = 0; i < pipeline->cmd_count - 1; i++)
	{
		if (pipe(pipe_fds[i]) == -1)
		{
			ft_putstr_fd("minishell: pipe creation failed\n", 2);
			exit(1);
		}
	}
}

static void	close_pipes(t_pipeline *pipeline, int **pipe_fds)
{
	int	i;

	for (i = 0; i < pipeline->cmd_count - 1; i++)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
	}
}

static void	setup_child_pipes(t_pipeline *pipeline, int **pipe_fds, int i)
{
	if (i > 0) // Not first command
	{
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
		close(pipe_fds[i - 1][1]);
	}
	if (i < pipeline->cmd_count - 1) // Not last command
	{
		dup2(pipe_fds[i][1], STDOUT_FILENO);
		close(pipe_fds[i][0]);
	}
}

static void	execute_piped_command(t_command *command, t_program *minishell)
{
	char	*cmd_path;

	if (command->is_builtin)
	{
		execute_builtin(command, minishell);
		exit(minishell->status);
	}
	cmd_path = find_command_path(command->arguments[0], minishell->envp);
	if (!cmd_path)
	{
		handle_execution_error(command, minishell, NULL, 1);
		exit(127);
	}
	execute_in_child(cmd_path, command, minishell);
}

void	execute_pipeline(t_pipeline *pipeline, t_program *minishell)
{
	int		**pipe_fds;
	pid_t	*pids;
	int		i;

	if (!pipeline || pipeline->cmd_count == 0)
		return ;
	if (pipeline->cmd_count == 1)
	{
		execute_command(pipeline->commands[0], minishell);
		return ;
	}
	pipe_fds = malloc(sizeof(int *) * (pipeline->cmd_count - 1));
	for (i = 0; i < pipeline->cmd_count - 1; i++)
		pipe_fds[i] = malloc(sizeof(int) * 2);
	pids = malloc(sizeof(pid_t) * pipeline->cmd_count);
	setup_pipes(pipeline, pipe_fds);
	for (i = 0; i < pipeline->cmd_count; i++)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			ft_putstr_fd("minishell: fork failed\n", 2);
			break ;
		}
		if (pids[i] == 0)
		{
			setup_child_pipes(pipeline, pipe_fds, i);
			close_pipes(pipeline, pipe_fds);
			execute_piped_command(pipeline->commands[i], minishell);
		}
	}
	close_pipes(pipeline, pipe_fds);
	for (i = 0; i < pipeline->cmd_count; i++)
		handle_execution_status(pids[i], minishell);
	for (i = 0; i < pipeline->cmd_count - 1; i++)
		free(pipe_fds[i]);
	free(pipe_fds);
	free(pids);
}
//redir
static int	setup_input_redirection(t_command *command)
{
	int	fd;

	if (command->input)
	{
		fd = open(command->input->filename, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(command->input->filename, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			return (1);
		}
		command->fd_in = fd;
		if (dup2(fd, STDIN_FILENO) == -1)
			return (1);
	}
	return (0);
}

static int	setup_output_redirection(t_command *command)
{
	int		fd;
	int		flags;
	char	*filename;

	if (command->output || command->append)
	{
		flags = O_WRONLY | O_CREAT;
		if (command->append)
		{
			flags |= O_APPEND;
			filename = command->append->filename;
		}
		else
		{
			flags |= O_TRUNC;
			filename = command->output->filename;
		}
		fd = open(filename, flags, 0644);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(filename, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			return (1);
		}
		command->fd_out = fd;
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (1);
	}
	return (0);
}

static void	cleanup_redirections(t_command *command)
{
	if (command->fd_in != -1)
	{
		close(command->fd_in);
		command->fd_in = -1;
	}
	if (command->fd_out != -1)
	{
		close(command->fd_out);
		command->fd_out = -1;
	}
}

static int	handle_redirections(t_command *command)
{
	if (setup_input_redirection(command))
		return (1);
	if (setup_output_redirection(command))
	{
		cleanup_redirections(command);
		return (1);
	}
	return (0);
}

void	execute_command(t_command *command, t_program *minishell)
{
	int	saved_stdin;
	int	saved_stdout;

	if (!command || !command->arguments || !command->arguments[0])
		return ;
	if (command->is_builtin)
	{
		saved_stdin = dup(STDIN_FILENO);
		saved_stdout = dup(STDOUT_FILENO);
		if (handle_redirections(command))
		{
			minishell->status = 1;
			return ;
		}
		execute_builtin(command, minishell);
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		cleanup_redirections(command);
	}
	else
		execute_external(command, minishell);
}

static void	execute_in_child(char *cmd_path, t_command *command,
		t_program *minishell)
{
	if (handle_redirections(command))
		exit(1);
	if (execve(cmd_path, command->arguments, minishell->envp) == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(command->arguments[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(cmd_path);
		exit(errno);
	}
}
