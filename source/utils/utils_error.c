#include "../../include/minishell.h"

void	error_command(char *command, t_program *minishell)
{
	ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
	if (command)
		ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	minishell->status = 127;
}

void	error_eof(char *token, t_program *minishell)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", STDERR_FILENO);
	if (token)
		ft_putstr_fd(token, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	minishell->status = 2;
}

void error_syntax(char *message, t_program *minishell)
{
	if (message && *message)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
	}
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
	ft_putstr_fd("minishell: too many arguments: ", STDERR_FILENO);
	if (command)
		ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	minishell->status = 1;
}

void	error_malloc(t_program *minishell)
{
	ft_putstr_fd("minishell: memory allocation failed\n", STDERR_FILENO);
	minishell->status = 1;
	(void)exit(minishell->status);
}

void error_unexpected_eof(t_program *minishell)
{
	ft_putstr_fd("minishell: unexpected end of file\n", STDERR_FILENO);
	minishell->status = 2;
}

void error_newline(t_program *minishell)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
	minishell->status = 2;
}

void error_brace(char *brace, t_program *minishell)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(brace, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	minishell->status = 2;
}

void error_permission(char *command, t_program *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	minishell->status = 126;
}

void error_directory(char *command, t_program *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": Is a directory\n", STDERR_FILENO);
	minishell->status = 126;
}

void error_not_found(char *command, t_program *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	minishell->status = 127;
}
