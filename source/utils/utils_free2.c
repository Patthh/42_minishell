/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:42:49 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:42:50 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_redirection(t_redirection *redirection)
{
	t_redirection	*temp;

	while (redirection)
	{
		temp = redirection;
		redirection = redirection->next;
		free(temp->type);
		free(temp->filename);
		free(temp->content);
		free(temp);
	}
}

void	free_command(t_command *command)
{
	int	i;

	i = 0;
	if (command == NULL)
		return ;
	if (command->arguments)
	{
		while (command->arguments[i])
		{
			free(command->arguments[i]);
			i++;
		}
		free(command->arguments);
	}
	free_redirection(command->input);
	free_redirection(command->output);
	free_redirection(command->append);
	free_redirection(command->heredoc);
	free(command);
}

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;

	i = 0;
	if (!pipeline)
		return ;
	while (i < pipeline->cmd_count)
	{
		if (pipeline->commands == NULL)
			return ;
		free_command(pipeline->commands[i]);
		pipeline->commands[i] = NULL;
		i++;
	}
	free(pipeline->commands);
	pipeline->commands = NULL;
	free(pipeline);
}
