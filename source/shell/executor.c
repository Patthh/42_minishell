/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pracksaw <pracksaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:30:17 by pracksaw          #+#    #+#             */
/*   Updated: 2025/01/25 18:30:18 by pracksaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	execute_external(t_command *command, t_program *minishell)
{
	char	*cmd_path;
	pid_t	pid;

	if (!command->arguments[0])
		return ;
	cmd_path = find_command_path(command->arguments[0], minishell);
	if (!cmd_path)
		return (handle_execution_error(command, minishell, NULL, 1));
	pid = fork();
	if (pid == -1)
	{
		handle_execution_error(command, minishell, cmd_path, 2);
		return ;
	}
	if (pid == 0)
	{
		if (execve(cmd_path, command->arguments, minishell->envp) == -1)
			exec_err_exit(command, cmd_path);
	}
	else
	{
		handle_execution_status(pid, minishell);
		free(cmd_path);
	}
}

void	execute_builtin(t_command *command, t_program *minishell)
{
	if (ft_strcmp(command->arguments[0], "echo") == 0)
		ft_echo(command, minishell);
	else if (ft_strcmp(command->arguments[0], "cd") == 0)
		ft_cd(command, minishell);
	else if (ft_strcmp(command->arguments[0], "pwd") == 0)
		ft_pwd(minishell);
	else if (ft_strcmp(command->arguments[0], "export") == 0)
		ft_export(command, minishell);
	else if (ft_strcmp(command->arguments[0], "unset") == 0)
		ft_unset(command, minishell);
	else if (ft_strcmp(command->arguments[0], "env") == 0)
		ft_env(minishell);
	else if (ft_strcmp(command->arguments[0], "exit") == 0)
		ft_exit(command, minishell);
}

// exec
void	execute_in_child(char *cmd_path, t_command *command,
		t_program *minishell)
{
	if (handle_redirections(command, minishell))
	{
		free(cmd_path);
		exit(1);
	}
	if (execve(cmd_path, command->arguments, minishell->envp) == -1)
	{
		ft_putstr_fd(command->arguments[0], STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(cmd_path);
		exit(errno);
	}
}

static void	restore_std_fds(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

		// minishell->status = 131;
void	execute_command(t_command *command, t_program *minishell)
{
	int	saved_stdin;
	int	saved_stdout;

	if (!command || !command->arguments || !command->arguments[0])
		return ;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdin == -1 || saved_stdout == -1)
	{
		if (saved_stdin != -1)
			close(saved_stdin);
		minishell->status = 1;
		return ;
	}
	if (handle_redirections(command, minishell))
		return (restore_std_fds(saved_stdin, saved_stdout));
	if (command->is_builtin)
		execute_builtin(command, minishell);
	else
		execute_external(command, minishell);
	restore_std_fds(saved_stdin, saved_stdout);
	cleanup_redirections(command);
}
