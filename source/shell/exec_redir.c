/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pracksaw <pracksaw@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:30:07 by pracksaw          #+#    #+#             */
/*   Updated: 2025/01/26 00:21:56 by pracksaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// static int	setup_input_redirection(t_command *command,
		// t_program *minishell)
// {
// 	int	fd;
// 	if (command->heredoc)
// 		return (setup_heredoc(command, minishell));
// 	if (command->input)
// 	{
// 		fd = open(command->input->filename, O_RDONLY);
// 		if (fd == -1)
// 		{
// 			ft_putstr_fd("minishell: ", STDERR_FILENO);
// 			ft_putstr_fd(command->input->filename, STDERR_FILENO);
// 			ft_putstr_fd(": ", STDERR_FILENO);
// 			ft_putstr_fd(strerror(errno), STDERR_FILENO);
// 			ft_putstr_fd("\n", STDERR_FILENO);
// 			return (1);
// 		}
// 		command->fd_in = fd;
// 		if (dup2(fd, STDIN_FILENO) == -1)
// 		{
// 			close(fd);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }
static int	setup_input_redirection(t_command *command, t_program *minishell)
{
	int				fd;
	t_redirection	*last_input;

	if (command->heredoc)
		return (setup_heredoc(command, minishell));
	last_input = command->input;
	while (last_input->next)
		last_input = last_input->next;
	fd = open(last_input->filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(last_input->filename, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		minishell->status = 1;
		return (1);
	}
	command->fd_in = fd;
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), 1);
	return (0);
}

static void	print_err_nofile(char *filename, t_program *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(filename, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	minishell->status = 1;
}

static int	setup_output_redirection(t_program *minishell, t_command *command)
{
	int				fd;
	int				flags;
	t_redirection	*last_output;

	if (!command->output && !command->append)
		return (0);
	if (command->append)
	{
		last_output = command->append;
		flags = O_WRONLY | O_CREAT | O_APPEND;
	}
	else
	{
		last_output = command->output;
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	}
	while (last_output->next)
		last_output = last_output->next;
	fd = open(last_output->filename, flags, 0644);
	if (fd == -1)
		return (print_err_nofile(last_output->filename, minishell), 1);
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
		if (setup_output_redirection(minishell, command))
		{
			cleanup_redirections(command);
			return (1);
		}
	}
	return (0);
}
