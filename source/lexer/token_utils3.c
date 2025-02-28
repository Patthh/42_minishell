/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:44:08 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:44:09 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// handles pipe and logical OR
static void	token_pipe(const char **input, t_token **head)
{
	if (*(*input + 1) == '|')
	{
		token_add(head, token_new(TKN_OR, "||"));
		(*input) += 2;
	}
	else
	{
		token_add(head, token_new(TKN_PIPE, "|"));
		(*input)++;
	}
}

// handle background and logical AND
static void	token_ampersand(const char **input, t_token **head)
{
	if (*(*input + 1) == '&')
	{
		token_add(head, token_new(TKN_AND, "&&"));
		(*input) += 2;
	}
	else
	{
		token_add(head, token_new(TKN_BG, "&"));
		(*input)++;
	}
}

// handles redirection tokens
void	token_operator(const char **input, t_token **head)
{
	if (**input == '|')
		token_pipe(input, head);
	else if (**input == '&')
		token_ampersand(input, head);
}

// helper to join strings and handle memory
char	*token_join(char *s1, const char *s2)
{
	char	*temp;

	if (!s1)
		return (ft_strdup(s2));
	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}

// helper function to handle regular characters
void	token_regular(const char **input, char **result)
{
	char	current[2];

	current[0] = **input;
	current[1] = '\0';
	*result = token_join(*result, current);
	(*input)++;
}
