/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:44:06 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:44:07 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// handle unquoted token
// allocate memory for temp
// handle $?
// handle regular character
void	token_unquoted(const char **input, char **result, t_program *minishell)
{
	char	*temp;
	char	*status;
	char	*c;

	temp = ft_strndup(*input, 2);
	if (temp && ft_strcmp(temp, "$?") == 0)
	{
		status = ft_itoa(minishell->status);
		*result = token_join(*result, status);
		free(status);
		*input += 2;
	}
	else
	{
		c = ft_strndup(*input, 1);
		*result = token_join(*result, c);
		free (c);
		(*input)++;
	}
	free(temp);
}

// process content within double quotes
// handles variable expansion
void	token_double(const char **input, char **result, t_program *minishell)
{
	char	*tmp;

	tmp = NULL;
	(*input)++;
	while (**input && **input != '"')
	{
		if (**input == '$')
			env_word(input, result, minishell);
		else
		{
			tmp = ft_strndup(*input, 1);
			if (tmp)
			{
				*result = token_join(*result, tmp);
				free(tmp);
				(*input)++;
			}
		}
	}
	if (**input == '"')
		(*input)++;
}

// process content within single quotes
// treat as literal
void	token_single(const char **input, char **result)
{
	const char	*start;
	char		*content;

	(*input)++;
	start = *input;
	while (**input && **input != '\'')
		(*input)++;
	if (**input)
	{
		content = ft_strndup(start, *input - start);
		*result = token_join(*result, content);
		free(content);
		(*input)++;
	}
}

void	token_assign(const char **input, t_token **head)
{
	char	*key;
	char	*value;

	key = ft_strndup(*input, ft_strchr(*input, '=') - *input);
	(*input) = ft_strchr(*input, '=') + 1;
	value = ft_strdup(*input);
	while (**input && !ft_isspace(**input))
		(*input)++;
	token_add(head, token_new(TKN_ASSIGN, ft_strjoin(key, value)));
	free(key);
	free(value);
}
