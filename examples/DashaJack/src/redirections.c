/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:42:05 by dsiroten          #+#    #+#             */
/*   Updated: 2024/10/11 18:58:12 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_input(t_tree *tree, int *open_fd, t_var **envp_list)
{
	int		fd;
	char	*file;

	if (open_fd == NULL)
	{
		file = get_filename(tree->left->data, envp_list);
		if (!file)
			return (1);
		fd = open(file, O_RDONLY);
		free(file);
		if (fd < 0)
			return (int_standard_error(NULL, tree->left->data));
	}
	else
		fd = *open_fd;
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	redirect_output_to_pipe(int *fd, t_var **envp_list, t_exec_state *state)
{
	int		fd_out;

	if (state->outfile != -1)
	{
		fd_out = state->outfile;
		if (fd != NULL)
			close(*fd);
	}
	else
		fd_out = *fd;
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd_out);
		return (1);
	}
	close(fd_out);
	state->outfile = -1;
	(void)envp_list;
	return (0);
}

int	redirect_output(t_tree *tree, t_var **envp_list, t_exec_state *state)
{
	int		fd;
	char	*file;

	file = get_filename(tree->left->data, envp_list);
	if (!file)
		return (1);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(file);
	if (fd < 0)
	{
		standard_error(NULL, tree->left->data);
		state->outfile = -1;
		return (1);
	}
	state->outfile = fd;
	return (0);
}

int	redirect_output_append(t_tree *tree, t_var **envp_list, t_exec_state *state)
{
	int		fd;
	char	*file;

	file = get_filename(tree->left->data, envp_list);
	if (!file)
		return (1);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	free(file);
	if (fd < 0)
	{
		standard_error(NULL, tree->left->data);
		state->outfile = -1;
		return (1);
	}
	state->outfile = fd;
	return (0);
}
