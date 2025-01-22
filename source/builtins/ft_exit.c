#include "../../include/minishell.h"
// // Exit the shell, returning a status of n to the shell’s parent.
// // If n is omitted, the exit status is that of the last command executed.
// // Any trap on EXIT is executed before the shell terminates.

// 	// no argument, use last exit status
// 	// if has argument, use it as exit status
// 	// check if argument is numeric
// 	// check if more than one argument
// 	// convert valid argument to integer
// 	// set program exit flag and return exit status
// // terminates the calling process

// // 1. No Argument: exit
// // 2. Valid Numeric Argument: exit 42
// // 3. Out-of-Range Argument: exit 777
// // 4. Negative Argument: exit -42
// // 5. Invalid Argument: exit asdasdasd
// // 6. Multiple Arguments: exit 1 2 3
// // 7. Empty Argument: exit ""
// // 8. Leading/Trailing Spaces: exit " 42 "
// // 9. Leading Zeros: exit 0042
// // 10. Non-Numeric Characters: exit 42abc

static int	exit_valid_argument(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static unsigned char	exit_status(const char *str)
{
	long long	num;
	int			i;
	int			sign;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	num *= sign;
	if (num < 0)
		return (256 + (num % 256));
	return (num % 256);
}

// no argument - exit with previous status
// checks if first argument is numeric
// checks if have more than one argument, no exit
// exits with status (modulo 256)
int	ft_exit(t_command *command, t_program *minishell)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (!command->arguments || !command->arguments[1])
		exit(minishell->status);
	if (!exit_valid_argument(command->arguments[1]))
	{
		error_numeric(command->arguments[1], minishell);
		exit(2);
	}
	if (command->arguments[2])
	{
		error_arguments(command->arguments[0], minishell);
		exit (1);
	}
	exit(exit_status(command->arguments[1]));
}
