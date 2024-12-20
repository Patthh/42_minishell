/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:40:08 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 15:50:12 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pipe(t_tree *tree, t_var **envp_list,
			t_exec_state *state, int *is_pipe)
{
	int	pid;

	pid = -1;
	if (tree->type == PIPE)
	{
		if (tree->left)
			pid = execute_cmd(tree, tree->left->data, envp_list, state);
		else
			state->status = empty_pipe(envp_list);
		*is_pipe = 1;
	}
	return (pid);
}

int	child_process(char *input_cmd, t_var *envp_list)
{
	char		**cmd;
	char		**envp;
	char		*cmd_path;
	struct stat	st;

	envp = build_envp(envp_list);
	if (!envp)
		return (1);
	cmd = parse_cmd(input_cmd, envp_list);
	if (!cmd[0])
		return (0);
	if (!cmd)
		return (m_error(envp));
	cmd_path = get_command_path(cmd[0], envp);
	if (!cmd_path)
		return (path_error(NULL, envp, cmd, 2));
	if (ft_strcmp(cmd_path, "PER") == 0)
		return (path_error(cmd_path, envp, cmd, 0));
	if (stat(cmd_path, &st) == 0 && S_ISDIR(st.st_mode))
		return (path_error(cmd_path, envp, cmd, 1));
	execve(cmd_path, cmd, envp);
	perror("minishell: execve");
	if (envp || cmd || cmd_path)
		free_child(envp, cmd, cmd_path);
	return (1);
}

int	execute_cmd(t_tree *tree, char *input_cmd,
			t_var **envp_list, t_exec_state *state)
{
	int		fds[2];
	int		status;
	pid_t	pid;

	if (create_pipe(fds, &(state->status)) != 0)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		syserror_fork(fds, &(state->status));
		return (-1);
	}
	if (pid == 0)
	{
		redirect_output_to_pipe(&fds[1], envp_list, state);
		close(fds[0]);
		if (!is_builtin(input_cmd, tree, envp_list, state))
			state->status = child_process(input_cmd, *envp_list);
		status = state->status;
		free_all(tree, *envp_list, state, status);
	}
	close(fds[1]);
	state->outfile = -1;
	redirect_input(NULL, &fds[0], envp_list);
	return (pid);
}

int	execute_last(t_tree *tree, char *input_cmd,
			t_var **envp_list, t_exec_state *state)
{
	int		pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		syserror_fork(NULL, &(state->status));
		return (-1);
	}
	if (pid == 0)
	{
		if (!is_builtin(input_cmd, tree, envp_list, state))
			state->status = child_process(input_cmd, *envp_list);
		status = state->status;
		free_all(tree, *envp_list, state, status);
	}
	return (pid);
}

void	free_child(char **envp, char **cmd, char *cmd_path)
{
	if (envp)
		free_arr(envp);
	if (cmd)
		free_arr(cmd);
	if (cmd_path)
		free(cmd_path);
}
