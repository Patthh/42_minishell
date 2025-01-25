/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:44:24 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:44:25 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	unset_free(t_env *env)
{
	if (env)
	{
		free(env->key);
		free(env->value);
		free(env);
	}
}

// removes env from list based on key
static int	unset_remove(t_program *minishell, const char *key)
{
	t_env	*current;
	t_env	*previous;

	if (!key)
		return (0);
	minishell->env_len--;
	current = minishell->env_list;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				minishell->env_list = current->next;
			unset_free(current);
			return (1);
		}
		previous = current;
		current = current->next;
	}
	return (0);
}

// validates variable name
// static int	unset_check(const char *name)
// {
// 	if (!name || !*name)
// 		return (0);
// 	if (ft_isalnum(*name) || *name == '_')
// 	{
// 		name++;
// 		while (*name)
// 		{
// 			if (!(ft_isalnum(*name) || *name == '_'))
// 				return (0);
// 			name++;
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

static int	unset_check(const char *name)
{
	if (!name || !*name)
		return (0);
	if (!(ft_isalnum(*name) || *name == '_'))
		return (0);
	while (*name)
	{
		if (!(ft_isalnum(*name) || *name == '_' || ft_isspecial(*name)))
			return (0);
		name++;
	}
	return (1);
}

// process a single argument
// check variable name
// remove variable from list
static int	unset_single(char *argument)
{
	if (!argument || !*argument)
		return (0);
	while (*argument)
	{
		if (!ft_isspace(*argument))
			break ;
		argument++;
	}
	if (!*argument)
		return (0);
	if (!unset_check(argument))
		return (0);
	return (1);
}

// unset command removes one or more env
int	ft_unset(t_command *command, t_program *minishell)
{
	int	i;
	int	status;

	if (!command->arguments || !command->arguments[1])
		return (0);
	i = 1;
	status = 0;
	while (command->arguments[i])
	{
		if (command->arguments[i][0] == '-')
		{
			error_option(command->arguments[i], minishell);
			return (1);
		}
		if (unset_single(command->arguments[i]) == 1)
		{
			unset_remove(minishell, command->arguments[i]);
		}
		i++;
	}
	minishell->status = status;
	return (status);
}
