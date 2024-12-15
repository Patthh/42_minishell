#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_program	minishell;

	(void)argc;
	(void)argv;
	init_shell(&minishell, envp);
	run_shell(&minishell);
	rl_clear_history();
	free_shell(&minishell);
	return (0);
}
