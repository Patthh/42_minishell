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

static void	ft_sigerror(const char *message)
{
	ft_putstr_fd((char *)message, STDERR_FILENO);
}

static void	ft_sigstat(int status)
{
	if (status == SIGHUP)
		ft_sigerror("Hangup\n");
	else if (status == SIGQUIT)
		ft_sigerror("Quit (core dumped)\n");
	else if (status == SIGILL)
		ft_sigerror("Illegal instruction (core dumped)\n");
	else if (status == SIGTRAP)
		ft_sigerror("Trace/breakpoint trap (core dumped)\n");
	else if (status == SIGABRT)
		ft_sigerror("Aborted (core dumped)\n");
	else if (status == SIGBUS)
		ft_sigerror("Bus error (core dumped)\n");
	else if (status == SIGFPE)
		ft_sigerror("Floating point exception (core dumped)\n");
	else if (status == SIGKILL)
		ft_sigerror("Killed\n");
	else if (status == SIGUSR1)
		ft_sigerror("User defined signal 1\n");
	else if (status == SIGSEGV)
		ft_sigerror("Segmentation fault (core dumped)\n");
	else if (status == SIGUSR2)
		ft_sigerror("User defined signal 1\n");
	else if (status == SIGPIPE)
		ft_sigerror("Broken pipe\n");
}

void	handle_execution_status(pid_t pid, t_program *minishell)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		minishell->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		minishell->status = 128 + WTERMSIG(status);
	if (status > 128)
		status = status - 128;
	ft_sigstat(status);
	if (status == SIGALRM)
		ft_sigerror("Alarm clock\n");
	else if (status == SIGTERM)
		ft_sigerror("Terminated\n");
	else if (status == SIGSTKFLT)
		ft_sigerror("Stack fault\n");
	else if (status == SIGIO)
		ft_sigerror("I/O possible\n");
	else if (status == SIGPWR)
		ft_sigerror("Power failure\n");
	else if (status == SIGSYS)
		ft_sigerror("Bad system call (core dumped)\n");
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
