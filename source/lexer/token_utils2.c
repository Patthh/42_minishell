/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:44:04 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:44:05 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// handles the creation of token based on redirection sequence
static void	token_redirector_create(char *value, t_token **head)
{
	if (ft_strcmp(value, "<<") == 0)
		token_add(head, token_new(TKN_RDH, "<<"));
	else if (ft_strcmp(value, ">>") == 0)
		token_add(head, token_new(TKN_RDA, ">>"));
	else if (ft_strcmp(value, "<") == 0)
		token_add(head, token_new(TKN_IN, "<"));
	else if (ft_strcmp(value, ">") == 0)
		token_add(head, token_new(TKN_OUT, ">"));
	else
		error_syntax(value, NULL);
}

// validates the redirection sequence
void	token_redirector(const char **input, t_token **head)
{
	int		i;
	char	value[3];

	i = 0;
	ft_memset(value, 0, 3);
	while ((**input == '<' || **input == '>') && i < 2)
	{
		value[i] = **input;
		(*input)++;
		i++;
	}
	if (i > 2 || (i == 2 && value[0] != value[1]))
	{
		error_syntax(value, NULL);
		return ;
	}
	token_redirector_create(value, head);
}
