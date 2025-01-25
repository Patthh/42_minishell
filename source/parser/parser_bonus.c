/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:43:44 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:43:45 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_command	**logical_pipeline(t_pipeline *pipeline,
	t_command *commands)
{
	t_command	**new;
	int			count;

	new = malloc(sizeof(t_command *) * pipeline->cmd_count);
	if (!new)
		ft_error("Parser: logical operator allocation failed\n");
	count = 0;
	while (pipeline->commands && count < pipeline->cmd_count - 1)
	{
		new[count] = pipeline->commands[count];
		count++;
	}
	free(pipeline->commands);
	new[count] = commands;
	return (new);
}

t_token	*parser_logical(t_token *token, t_command **command,
	t_pipeline *pipeline)
{
	t_command	*new;

	new = create_command();
	if (*command)
	{
		(*command)->next = new;
		if (token->type == TKN_AND)
			(*command)->logical = LOG_AND;
		else
			(*command)->logical = LOG_OR;
	}
	pipeline->cmd_count++;
	pipeline->commands = logical_pipeline(pipeline, new);
	*command = new;
	return (token->next);
}

t_token	*parser_wildcard(t_token *token, t_command *command)
{
	if (!token || !command)
		return (NULL);
	if (!parser_argument(command, token->value))
		ft_error("Parser: failed to add wildcard argument\n");
	return (token->next);
}

// t_token	*parser_parantheses(t_token *token, t_pipeline *pipeline)
// {

// }
