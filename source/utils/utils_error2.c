/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:46:30 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:46:51 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_not_valid_identifier(char *command, t_program *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putstr_fd(": not a valid identifier\n", STDERR_FILENO);
	minishell->status = 127;
}

void	error_out_of_range(char *argument, t_program *minishell)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(argument, STDERR_FILENO);
	ft_putstr_fd(": numeric argument out of range\n", STDERR_FILENO);
	minishell->status = 2;
}

void	error_option(char *argument, t_program *minishell)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(argument, STDERR_FILENO);
	ft_putstr_fd(": invalid option\n", STDERR_FILENO);
	minishell->status = 2;
}

void	error_no_match(char *pattern, t_program *minishell)
{
	ft_putstr_fd("minishell: cannot access: `", STDERR_FILENO);
	ft_putstr_fd(pattern, STDERR_FILENO);
	ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
	minishell->status = 2;
}

void	error_heredoc(char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line 1 \
		delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')", STDERR_FILENO);
	rl_clear_history();
}
