/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pracksaw <pracksaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:30:50 by pracksaw          #+#    #+#             */
/*   Updated: 2025/01/25 18:30:51 by pracksaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	write_pipe(int fd[2], t_command *command)
{
	size_t	len;
	ssize_t	written;

	close(fd[0]);
	len = ft_strlen(command->heredoc->content);
	written = write(fd[1], command->heredoc->content, len);
	write(fd[1], "\n", 1);
	close(fd[1]);
	if (written == -1)
		exit(1);
	exit(0);
}

void	close_both(int fd1, int fd2)
{
	if (fd1 != -1)
		close(fd1);
	if (fd2 != -1)
		close(fd2);
}

void	update_exit_status(pid_t pid, int fd[2], t_program *minishell)
{
	int		status;

	waitpid(pid, &status, 0);
	close(fd[0]);
	if (WIFEXITED(status))
		minishell->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		minishell->status = 128 + WTERMSIG(status);
}

void	close_err(int fd1, int fd2)
{
	close_both(fd1, fd2);
	ft_error("minishell: fork failed");
}

int	setup_heredoc(t_command *command, t_program *minishell)
{
	int		fd[2];
	pid_t	pid;
	int		saved_stdin;

	if (!command || !command->heredoc)
		return (1);
	if (pipe(fd) == -1)
		return (ft_error("minishell: pipe failed"), 1);
	pid = fork();
	if (pid == -1)
		return (close_err(fd[0], fd[1]), 1);
	if (pid == 0)
		write_pipe(fd, command);
	else
	{
		close(fd[1]);
		saved_stdin = dup(STDIN_FILENO);
		if (saved_stdin == -1)
			return (close(fd[0]), 1);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (close_both(fd[0], saved_stdin), 1);
		update_exit_status(pid, fd, minishell);
		return (0);
	}
	return (0);
}
