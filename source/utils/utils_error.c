#include "../../include/minishell.h"

// void	error_command(char *command, t_program *minishell)
// {
// 	if (ft_strcmp(command, "$?") == 0)
// 	{
// 		ft_putstr_fd("1: command not found\n", STDERR_FILENO);
// 		minishell->status = 127;
// 		return ;
// 	}
// 	ft_putstr_fd("minishell: ", STDERR_FILENO);
// 	ft_putstr_fd(command, STDERR_FILENO);
// 	ft_putstr_fd(": command not found\n", STDERR_FILENO);
// 	minishell->status = 127;
// }

void	error_command(char *command, t_program *minishell)
{
	char	*status_str;

	if (ft_strcmp(command, "$?") == 0)
	{
		status_str = ft_itoa(minishell->status);
		if (status_str)
		{
			ft_putstr_fd(status_str, STDERR_FILENO);
			ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
			free(status_str);
		}
	}
	else
	{
		ft_putstr_fd(command, STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	}
	minishell->status = 127;
}

void	error_eof(char *token, t_program *minishell)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `",
		STDERR_FILENO);
	if (token)
		ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	minishell->status = 2;
}

void	error_syntax(char *token, t_program *minishell)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	if (token && *token)
		ft_putstr_fd(token, STDERR_FILENO);
	else
		ft_putstr_fd("newline", STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	minishell->status = 2;
}

void	error_file_not_found(char *path, t_program *minishell)
{
	ft_putstr_fd("minishell: file not found: ", STDERR_FILENO);
	if (path)
		ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	minishell->status = 1;
}

void	error_arguments(char *command, t_program *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
	minishell->status = 1;
}

void	error_malloc(t_program *minishell)
{
	ft_putstr_fd("minishell: memory allocation failed\n", STDERR_FILENO);
	minishell->status = 1;
	(void)exit(minishell->status);
}

void	error_unexpected_eof(t_program *minishell)
{
	ft_putstr_fd("minishell: unexpected end of file\n", STDERR_FILENO);
	minishell->status = 2;
}

// void	error_newline(t_program *minishell)
// {
// 	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
// 		STDERR_FILENO);
// 	minishell->status = 2;
// }

void	error_brace(char *brace, t_program *minishell)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(brace, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	minishell->status = 2;
}

void	error_permission(char *command, t_program *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	minishell->status = 126;
}

void	error_directory(char *command, t_program *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	minishell->status = 126;
}

void	error_not_found(char *path, t_program *minishell)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	minishell->status = 1;
}

void	error_numeric(char *command, t_program *minishell)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	minishell->status = 2;
}

void	error_identifier(char *identifier, t_program *minishell)
{
	ft_putstr_fd("minishell: unset: ", STDERR_FILENO);
	ft_putstr_fd(identifier, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	minishell->status = 1;
}

void	error_file_not_found_127(char *path, t_program *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	minishell->status = 127;
}

void	error_not_valid_identifier(char *command, t_program *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	minishell->status = 127;
}

void	error_out_of_range(char *argument, t_program *minishell)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(argument, STDERR_FILENO);
	ft_putstr_fd(": numeric argument out of range\n", STDERR_FILENO);
	minishell->status = 2;
}

void	error_option(char *argument, t_program *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(argument, STDERR_FILENO);
	ft_putstr_fd(": invalid option\n", STDERR_FILENO);
	minishell->status = 2;
}
