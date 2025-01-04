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
static int	exit_number(const char *string, char **end)
{
	if (!string || !end)
		return (0);
	ft_strtol(string, end);
	if (!*end)
		return (0);
	if (*end == string)
		return (0);
	if (**end != '\0')
		return (0);
	if (errno == ERANGE)
		return (-1);
	return (1);
}

static int	exit_arguments(t_program *minishell)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	minishell->status = 1;
	return (1);
}

static int	exit_set(t_program *minishell, int status, char *argument)
{
	if (argument)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argument, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		status = 2;
	}
	minishell->status = status;
	minishell->exit = TRUE;
	shell_exit(NULL, NULL, minishell);
	return (status);
}

// count the number of arguments
// case 1: no argument
// case 2: more than one argument
// case 3: single argument
//			check not number or out-of-range argument
int	ft_exit(t_command *command, t_program *minishell)
{
	int		length;
	long	status;
	char	*end;

	length = 0;
	end = NULL;
	while (command->arguments[length])
		length++;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (length == 1)
		return (exit_set(minishell, minishell->status, NULL));
	if (length > 2)
		return (exit_arguments(minishell));
	status = ft_strtol(command->arguments[1], &end);
	if (exit_number(command->arguments[1], &end) < 0)
	{
		exit_set(minishell, 0, command->arguments[1]);
		return (2);
	}
	exit_set(minishell, status, NULL);
	return (status);
}
