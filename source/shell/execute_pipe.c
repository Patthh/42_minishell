/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pracksaw <pracksaw@student.42bangkok.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:30:13 by pracksaw          #+#    #+#             */
/*   Updated: 2025/01/26 00:18:20 by pracksaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	run_piped_command(t_pipeline *pipeline, int **pipe_fds, int i,
		t_program *minishell)
{
	setup_child_pipes(pipeline, pipe_fds, i);
	close_pipes(pipeline, pipe_fds);
	execute_piped_command(pipeline->commands[i], minishell);
}

static void	create_pipeline_processes(t_pipeline *pipeline, pid_t *pids,
		int **pipe_fds, t_program *minishell)
{
	int	i;

	i = 0;
	while (i < pipeline->cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			ft_putstr_fd("minishell: fork failed\n", 2);
			break ;
		}
		if (pids[i] == 0)
			run_piped_command(pipeline, pipe_fds, i, minishell);
		i++;
	}
}

static void	cleanup_pipeline(t_pipeline *pipeline, t_program *minishell,
		pid_t *pids, int **pipe_fds)
{
	int	i;

	close_pipes(pipeline, pipe_fds);
	i = 0;
	while (i < pipeline->cmd_count)
	{
		handle_execution_status(pids[i], minishell);
		i++;
	}
	i = 0;
	while (i < pipeline->cmd_count - 1)
	{
		free(pipe_fds[i]);
		i++;
	}
}

void	execute_pipeline(t_pipeline *pipeline, t_program *minishell)
{
	int		**pipe_fds;
	pid_t	*pids;
	int		i;

	i = 0;
	if (!pipeline || pipeline->cmd_count == 0)
		return ;
	if (pipeline->cmd_count == 1)
		return (execute_command(pipeline->commands[0], minishell));
	pipe_fds = malloc(sizeof(int *) * (pipeline->cmd_count - 1));
	while (i < pipeline->cmd_count - 1)
	{
		pipe_fds[i] = malloc(sizeof(int) * 2);
		i++;
	}
	pids = malloc(sizeof(pid_t) * pipeline->cmd_count);
	setup_pipes(pipeline, pipe_fds);
	create_pipeline_processes(pipeline, pids, pipe_fds, minishell);
	cleanup_pipeline(pipeline, minishell, pids, pipe_fds);
	free(pipe_fds);
	free(pids);
}
