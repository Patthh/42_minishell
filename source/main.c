#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_program	minishell;

	init_shell(&minishell, envp);

	run_shell(&minishell);

	rl_clear_history();
	free_shell(&minishell);
	return (0);
}
