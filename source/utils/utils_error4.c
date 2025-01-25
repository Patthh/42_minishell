/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:47:19 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:47:47 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_arguments(char *command, t_program *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": too many arguments\n", STDERR_FILENO);
	minishell->status = 1;
}

void	error_malloc(t_program *minishell)
{
	ft_putstr_fd("minishell: memory allocation failed\n", STDERR_FILENO);
	minishell->status = 1;
	(void)exit(minishell->status);
}

void	error_unexpected_eof(t_program *minishell)
{
	ft_putstr_fd("minishell: unexpected end of file\n", STDERR_FILENO);
	minishell->status = 2;
}

void	error_brace(char *brace, t_program *minishell)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(brace, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	minishell->status = 2;
}

void	error_permission(char *command, t_program *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": Permission denied\n", STDERR_FILENO);
	minishell->status = 126;
}
