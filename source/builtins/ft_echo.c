#include "../../include/minishell.h"

// echo -n
// echo -n -n
// echo -n -n -n hello              is valid
// skips all -n flags
// cc ft_echo.c ../utils/utils_libft.c
// run ./a.out -n argument
// flag -n do not output the trailing newline
int	ft_echo(t_command *command, t_program *minishell)
{
	int	i;
	int	nl;

	i = 1;
	nl = 0;
	while (command->arguments[i] && ft_strcmp(command->arguments[i], "-n") == 0)
	{
		nl = 1;
		i++;
	}
	while (command->arguments[i])
	{
		ft_putstr_fd(command->arguments[i], STDOUT_FILENO);
		if (command->arguments[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (!nl)
		ft_putstr_fd("\n", STDOUT_FILENO);
	minishell->status = 0;
	return (0);
}

// int main(int argc, char **argv)
// {
// 	t_command	command;
// 	t_program	minishell;

// 	(void)argc;
// 	command.arguments = argv;

// 	ft_echo(&command, &minishell);
// 	// printf("Exit status: %d\n", minishell.status);
// 	return (0);
// }
