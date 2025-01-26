/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pracksaw <pracksaw@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:30:21 by pracksaw          #+#    #+#             */
/*   Updated: 2025/01/26 00:24:42 by pracksaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	setup_pipes(t_pipeline *pipeline, int **pipe_fds)
{
	int	i;

	i = 0;
	while (i < pipeline->cmd_count - 1)
	{
		if (pipe(pipe_fds[i]) == -1)
		{
			ft_putstr_fd("minishell: pipe creation failed\n", 2);
			exit(1);
		}
		i++;
	}
}

void	close_pipes(t_pipeline *pipeline, int **pipe_fds)
{
	int	i;

	i = 0;
	while (i < pipeline->cmd_count - 1)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
}

void	setup_child_pipes(t_pipeline *pipeline, int **pipe_fds, int i)
{
	if (i > 0)
	{
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
		close(pipe_fds[i - 1][1]);
	}
	if (i < pipeline->cmd_count - 1)
	{
		dup2(pipe_fds[i][1], STDOUT_FILENO);
		close(pipe_fds[i][0]);
	}
}

void	execute_piped_command(t_command *command, t_program *minishell)
{
	char	*cmd_path;

	if (handle_redirections(command, minishell) != 0)
		exit (1);
	if (command->is_builtin)
	{
		execute_builtin(command, minishell);
		exit(minishell->status);
	}
	cmd_path = find_command_path(command->arguments[0], minishell);
	if (!cmd_path)
	{
		handle_execution_error(command, minishell, NULL, 1);
		exit(127);
	}
	execute_in_child(cmd_path, command, minishell);
}
