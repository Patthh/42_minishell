#include "../include/minishell.h"

void	nl_handler(int signal)
{
	write(1, "\n", STDOUT_FILENO);
	rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    (void)signal;
}
