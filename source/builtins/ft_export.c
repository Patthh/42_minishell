/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pracksaw <pracksaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:33:23 by pracksaw          #+#    #+#             */
/*   Updated: 2025/01/25 18:33:24 by pracksaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// handles without memory leaks
// export
// export a
// export b=
// export c=qwe
// export d="qwe"
// export e='qwe'
// export f=""
// export g=''
// export a b c d e f g h
// export VAR=$USER
// export =
// export "="

// extracts key and value from argument
// handles special case where argument is "="
void	export_extract(const char *argument, char **key,
	char **value, int *sign)
{
	char	*equals;

	equals = ft_strchr(argument, '=');
	if (equals)
	{
		*key = ft_strndup(argument, equals - argument);
		*value = ft_strdup(equals + 1);
		*sign = 0;
	}
	else
	{
		*key = ft_strdup(argument);
		*value = NULL;
		*sign = 1;
	}
}

// extracts key and value from argument
// validates the key
// process if valid key
int	export_process(const char *argument, t_program *minishell)
{
	char	*key;
	char	*value;
	int		sign;

	export_extract(argument, &key, &value, &sign);
	if (!export_valid(key))
	{
		export_error(argument, minishell);
		free_key_value(key, value);
		return (1);
	}
	if (key && *key)
		export_update(minishell, key, value, sign);
	free_key_value(key, value);
	return (0);
}

// handles export command
void	ft_export(t_command *command, t_program *minishell)
{
	int	i;

	if (!command->arguments[1])
		print_export(minishell);
	else
	{
		i = 1;
		while (command->arguments[i])
		{
			export_process(command->arguments[i], minishell);
			i++;
		}
	}
}
