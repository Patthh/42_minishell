/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:42:38 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:42:39 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// tracks open/closed single and double quotes
int	quote_tracker(const char *input)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*input)
	{
		if (*input == '\'')
		{
			if (!double_quote)
				single_quote = !single_quote;
		}
		else if (*input == '"')
		{
			if (!single_quote)
				double_quote = !double_quote;
		}
		input++;
	}
	return (!(single_quote || double_quote));
}

// tracks open/closed parentheses
int	parentheses_tracker(const char *input)
{
	int	parentheses;

	parentheses = 0;
	while (*input)
	{
		if (*input == '(')
			parentheses++;
		else if (*input == ')')
		{
			if (parentheses == 0)
				return (0);
			parentheses--;
		}
		input++;
	}
	return (parentheses == 0);
}

char	*ft_multjoin(char **arr_str)
{
	char	*res;
	char	*tmp;

	if (!arr_str && !*arr_str)
		return (NULL);
	res = ft_strdup(*arr_str++);
	while (*arr_str)
	{
		tmp = ft_strjoin(res, *arr_str);
		free(res);
		res = tmp;
		arr_str++;
	}
	return (tmp);
}

void	gen_env(t_program *minishell)
{
	t_env	*tmp;
	size_t	i;

	if (minishell->envp != NULL)
		free_environ(minishell->envp);
	i = 0;
	minishell->envp = malloc(sizeof(*minishell->envp) * (minishell->env_len
				+ 1));
	tmp = minishell->env_list;
	while (tmp)
	{
		minishell->envp[i++] = ft_multjoin((char *[]){tmp->key, "=", tmp->value,
				NULL});
		tmp = tmp->next;
	}
	minishell->envp[i] = NULL;
}
