#include "../../include/minishell.h"

void	cleanup_redirections(t_command *command)
{
	if (!command)
		return ;
	if ((command->input) && command->fd_in != -1)
	{
		close(command->fd_in);
		command->fd_in = -1;
	}
	if ((command->output || command->append) && command->fd_out != -1)
	{
		close(command->fd_out);
		command->fd_out = -1;
	}
}

static int	setup_input_redirection(t_command *command, t_program *minishell)
{
	int	fd;

	if (command->heredoc)
		return (setup_heredoc(command, minishell));
	if (command->input)
	{
		fd = open(command->input->filename, O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("minishell: ", STDERR_FILENO);
			ft_putstr_fd(command->input->filename, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			ft_putstr_fd("\n", STDERR_FILENO);
			return (1);
		}
		command->fd_in = fd;
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			return (1);
		}
	}
	return (0);
}

static void	print_err_nofile(char *filename)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static int	setup_output_redirection(t_command *command)
{
	int		fd;
	int		flags;
	char	*filename;

	if (!command->output && !command->append)
		return (0);
	if (command->append)
	{
		flags = O_WRONLY | O_CREAT | O_APPEND;
		filename = command->append->filename;
	}
	else
	{
		flags = O_WRONLY | O_CREAT | O_TRUNC;
		filename = command->output->filename;
	}
	fd = open(filename, flags, 0644);
	if (fd == -1)
		return (print_err_nofile(filename), 1);
	command->fd_out = fd;
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), 1);
	return (0);
}

int	handle_redirections(t_command *command, t_program *minishell)
{
	if (!command)
		return (1);
	if (command->heredoc)
	{
		if (setup_heredoc(command, minishell))
			return (1);
	}
	if (command->input && !command->heredoc)
	{
		if (setup_input_redirection(command, minishell))
		{
			cleanup_redirections(command);
			return (1);
		}
	}
	if (command->output || command->append)
	{
		if (setup_output_redirection(command))
		{
			cleanup_redirections(command);
			return (1);
		}
	}
	return (0);
}
