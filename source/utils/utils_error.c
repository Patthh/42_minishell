/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:43:00 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:47:41 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
