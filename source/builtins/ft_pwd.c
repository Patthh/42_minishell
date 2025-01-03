#include "../../include/minishell.h"

int	ft_pwd(t_program *minishell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_putstr_fd("pwd: error retrieving current directory", STDERR_FILENO);
		minishell->status = 1;
		return (1);
	}
	ft_putstr_fd(cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	free(cwd);
	minishell->status = 0;
	return (0);
}

// int main(void)
// {
// 	t_program minishell;

// 	ft_pwd(&minishell);
// 	return (0);
// }
