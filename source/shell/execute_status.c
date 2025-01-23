#include "../../include/minishell.h"

void	handle_execution_error(t_command *command, t_program *minishell,
		char *cmd_path, int error_type)
{
	if (error_type == 1)
	{
		ft_putstr_fd(command->arguments[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		minishell->status = 127;
	}
	else if (error_type == 2)
	{
		ft_putstr_fd("minishell: fork failed\n", 2);
		minishell->status = 1;
	}
	free(cmd_path);
}

void	handle_execution_status(pid_t pid, t_program *minishell)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		minishell->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		minishell->status = 128 + WTERMSIG(status);
}

void	exec_err_exit(t_command *command, char *cmd_path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command->arguments[0], STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free(cmd_path);
	exit(errno);
}
