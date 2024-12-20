/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hell.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichompo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:13:45 by jichompo          #+#    #+#             */
/*   Updated: 2024/12/19 16:13:46 by jichompo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	m_error(char **envp)
{
	perror("minishell: malloc");
	free_arr(envp);
	return (1);
}

int	path_error(char *cmd_path, char **envp, char **cmd, int error)
{
	if (error == 2)
	{
		free_child(envp, cmd, NULL);
		return (127);
	}
	if (error == 1)
	{
		custom_error(*cmd, NULL, "Is a directory");
		free_child(envp, cmd, cmd_path);
		return (126);
	}
	if (error == 0)
		return (126);
	return (126);
}

int	int_standard_error(char *cmd, char *arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}
