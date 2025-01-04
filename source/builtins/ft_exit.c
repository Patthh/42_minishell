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

static int	exit_arguments(char *argument, long *status)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (argument[i] && ft_isspace(argument[i]))
		i++;
	j = i;
	while (argument[j] && !ft_isspace(argument[j]))
	j++;
	if (exit_number(argument + i, NULL) < 0)
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argument, STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		return (2);
	}
	*status = ft_strtol(argument + i, NULL);
	if (*status < 0 || *status > 255)
		*status = *status % 256;
	return (0);
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
// different error message for too many argument
int	ft_exit(t_command *command, t_program *minishell)
{
	int		length;
	long	status;

	length = 0;
	while (command->arguments[length])
		length++;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (length == 1)
		return (exit_set(minishell, minishell->status, NULL));
	if (length > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (exit_set(minishell, 1, NULL));
	}
	if (exit_arguments(command->arguments[1], &status) != 0)
		return (exit_set(minishell, 2, command->arguments[1]));
	exit_set(minishell, status, NULL);
	return (status);
}
