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

// 1. No Argument: exit
// 2. Valid Numeric Argument: exit 42
// 3. Out-of-Range Argument: exit 777
// 4. Negative Argument: exit -42
// 5. Invalid Argument: exit asdasdasd
// 6. Multiple Arguments: exit 1 2 3
// 7. Empty Argument: exit ""
// 8. Leading/Trailing Spaces: exit " 42 "
// 9. Leading Zeros: exit 0042
// 10. Non-Numeric Characters: exit 42abc

static int	exit_number(const char *string, char **end)
{
	if (!string || !end)
		return (0);
	*end = (char *)string;
	ft_strtol(string, end);
	if (*end == string || **end != '\0' || errno == ERANGE)
		return (-1);
	return (1);
}

static int	exit_arguments(char *argument, long *status, t_program *minishell)
{
	char	*end;

	if (exit_number(argument, &end) < 0)
	{
		error_numeric(argument, minishell);
		return (2);
	}
	*status = ft_strtol(argument, &end);
	if (*status < 0 || *status > 255)
		*status = *status % 256;
	return (0);
}

static int	exit_set(t_program *minishell, int status)
{
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
// different error message for too many argument
int	ft_exit(t_command *command, t_program *minishell)
{
	int		length;
	long	status;

	length = 0;
	while (command->arguments[length])
		length++;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (length == 1)
		return (exit_set(minishell, minishell->status));
	if (length > 2)
	{
		error_arguments("exit", minishell);
		return (exit_set(minishell, 1));
	}
	if (exit_arguments(command->arguments[1], &status, minishell) != 0)
		return (exit_set(minishell, 2));
	exit_set(minishell, status);
	return (status);
}
