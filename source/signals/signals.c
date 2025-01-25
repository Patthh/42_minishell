#include "../include/minishell.h"

void	nl_handler(int signal)
{
	write(1, "\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void)signal;
}

void	cwd_exit(char *cwd)
{
	free(cwd);
	ft_putendl_fd("exit", STDERR_FILENO);
	exit(EXIT_SUCCESS);
}

void	handle_sigquit(int sig)
{
	(void)sig;
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

// void update_shlvl(t_program *program)
// {
//     t_env *shlvl_node;
//     int num_val;
//     char *shlvl;

//     shlvl_node = env_find(program->env_list, "SHLVL");
//     if (!shlvl_node)
//     {
//         export_process("SHLVL=1", program);
//         return ;
//     }
//     shlvl = shlvl_node->value;
//     num_val = ft_atoi(shlvl);
//     num_val++;
//     free(shlvl_node->value);
//     shlvl_node->value = ft_itoa(num_val);
//     if (!shlvl_node->value)
//     {
//         perror("ft_itoa");
//         exit(EXIT_FAILURE);
//     }
// }
void	update_shlvl(t_program *program)
{
	t_env	*shlvl_node;
	int		num_val;

	shlvl_node = env_find(program->env_list, "SHLVL");
	if (shlvl_node)
	{
		num_val = ft_atoi(shlvl_node->value);
		num_val++;
		free(shlvl_node->value);
		shlvl_node->value = ft_itoa(num_val);
		if (!shlvl_node->value)
		{
			perror("ft_itoa");
			exit(EXIT_FAILURE);
		}
	}
}
