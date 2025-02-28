/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:42:34 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:42:35 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_error(const char *message)
{
	ft_putstr_fd((char *)message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	ft_isnumeric(const char *string)
{
	while (*string)
	{
		if (!ft_isdigit(*string))
			return (0);
		string++;
	}
	return (1);
}

int	ft_isspecial(char c)
{
	const char	*special_chars = "!@#$%^&*()-_=+[]{}|;:,.<>?/~`";

	while (*special_chars)
	{
		if (c == *special_chars)
			return (1);
		special_chars++;
	}
	return (0);
}

int	ft_isredirect_token(t_token *token)
{
	if (token->type == TKN_IN || token->type == TKN_OUT
		|| token->type == TKN_RDA || token->type == TKN_RDH)
		return (1);
	return (0);
}
