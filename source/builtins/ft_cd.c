// #include "../../include/minishell.h"

// static void	update_cd(t_program *minishell)
// {
// 	char	*cwd;
// 	char	*old;

// 	cwd = getcwd(NULL, 0);
// 	if (!cwd)
// 	{
// 		ft_putstr_fd("cd: error retrieving current driectory\n", STDERR_FILENO);
// 		return ;
// 	}
// 	old = getenv(minishell, "PWD");
// }

// // chdir - change working directory
// // strerror - return string describing error number
// int	ft_cd(t_command *command, t_program *minishell)
// {
// 	char	*directory;

// 	if (!command->arguments[1])
// 	{
// 		ft_putstr_fd("cd: missing directory argument\n", STDERR_FILENO);
// 		minishell->status = 1;
// 		return (1);
// 	}
// 	directory = command->arguments[1];
// 	if (chdir(directory) == -1)
// 	{
// 		ft_putstr_fd("cd: ", STDERR_FILENO);
// 		ft_putstr_fd(directory, STDERR_FILENO);
// 		ft_putstr_fd(": ", STDERR_FILENO);
// 		ft_putstr_fd(strerror(errno), STDERR_FILENO);
// 		ft_putstr_fd("\n", STDERR_FILENO);
// 		minishell->status = 1;
// 		return (1);
// 	}
// 	update_cd(minishell);
// 	minishell->status = 0;
// 	return (0);
// }
