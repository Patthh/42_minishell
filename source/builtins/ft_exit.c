#include "../../include/minishell.h"

// Exit the shell, returning a status of n to the shell’s parent.
// If n is omitted, the exit status is that of the last command executed.
// Any trap on EXIT is executed before the shell terminates.

	// no argument, use last exit status
	// if has argument, use it as exit status
	// check if argument is numeric
	// check if more than one argument
	// convert valid argument to integer
	// set program exit flag and return exit status

// terminates the calling process
int	ft_exit(t_command *command, t_program *minishell)
{
	int		status;
	char	*end;

	end = NULL;
	ft_putstr_fd("exit\n", STDOUT_FILENO); // or STDERR_FILENO ?
	if (!command->arguments[1])
		status = minishell->status;
	else
	{
		status = ft_strtol(command->arguments[1], &end);
		if (end == NULL || *end != '\0' || command->arguments[2])
		{
			ft_putstr_fd("exit: numeric argument required\n", STDERR_FILENO);
			return (1);
		}
		if (errno == ERANGE)
		{
			ft_putstr_fd("exit: numeric argument out of range\n", STDERR_FILENO);
			return (2);
		}
	}
	minishell->exit = TRUE;
	return (status);
}
