/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pracksaw <pracksaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:36:33 by pracksaw          #+#    #+#             */
/*   Updated: 2025/01/25 18:36:34 by pracksaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_key_value(char *key, char *value)
{
	if (key)
		free (key);
	if (value)
		free (value);
}

static int	ft_export_valid(const char *key)
{
	if (ft_isdigit(key[0]))
		return (0);
	if (ft_strchr(key, '-') || ft_strchr(key, '+') || ft_strchr(key, '.')
		|| ft_strchr(key, '@') || ft_strchr(key, '!') || ft_strchr(key, '^')
		|| ft_strchr(key, '~') || ft_strchr(key, '#') || ft_strchr(key, '*'))
		return (0);
	return (1);
}

// validates variable names
// checks for empty string or null
// first char must be letter or underscore
// rest of string must be alphanumeric of underscore
int	export_valid(const char *string)
{
	const char	*check;

	check = string;
	if (!string || !*string)
		return (0);
	if (!ft_isalpha(*string) && *string != '_')
		return (0);
	string++;
	while (*string)
	{
		if (!ft_isalnum(*string) && *string != '_')
			return (0);
		string++;
	}
	if (!ft_export_valid(check))
		return (0);
	return (1);
}

// prints error message for invalid identifiers
void	export_error(const char *argument, t_program *minishell)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd((char *)argument, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	minishell->status = 1;
}

// updates and adds env with value expansion
// handle case with no value
// expand any variables in the value
void	export_update(t_program *minishell, char *key, char *value, int sign)
{
	char	*expand;

	export_remove(minishell, key);
	if (!value || ft_strcmp(value, "") == 0)
	{
		add_env(minishell, key, "", sign);
		return ;
	}
	expand = quote_expand(value, minishell);
	if (!expand)
	{
		add_env(minishell, key, "", sign);
		return ;
	}
	add_env(minishell, key, expand, sign);
	free(expand);
}
