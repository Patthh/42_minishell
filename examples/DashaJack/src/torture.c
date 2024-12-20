/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jichompo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:43:32 by jichompo          #+#    #+#             */
/*   Updated: 2024/12/13 15:43:36 by jichompo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	expand_filename(char *input, t_var **envp_list, char *arg)
{
	int	arg_index;
	int	in_single_quote;
	int	in_double_quote;

	arg_index = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (*input)
	{
		if (toggle_quotes(*input, &in_single_quote, &in_double_quote))
		{
			input++;
			continue ;
		}
		if (!in_single_quote && expand_var(&input, arg, &arg_index, *envp_list))
			continue ;
		else
			add_char_to_arg(arg, *input, &arg_index);
		input++;
	}
	return (!(in_single_quote || in_double_quote));
}

char	*get_filename(char *input, t_var **envp_list)
{
	char	*arg;
	int		is_valid;

	arg = malloc(ARG_MAX + 1);
	ft_memset((void *)arg, 0, ARG_MAX + 1);
	if (!arg)
		return (NULL);
	is_valid = expand_filename(input, envp_list, arg);
	if (!is_valid)
	{
		free(arg);
		custom_error(NULL, NULL, "Quote not closed");
		return (NULL);
	}
	return (arg);
}

void	free_list(t_link_list **current)
{
	t_link_list	*temp;

	while (*current && (*current)->next)
	{
		temp = (*current)->next;
		free_node(*current);
		*current = temp;
	}
	if (*current)
		free_node(*current);
}

char	*ft_join(t_link_list **current)
{
	char		*str;
	t_link_list	*temp;

	temp = *current;
	str = malloc(sizeof(char) + 1);
	if (!str)
		return (NULL);
	*str = '\0';
	while (temp)
	{
		str = ft_free_strjoin(str, temp->data);
		str = ft_free_strjoin(str, " ");
		temp = temp->next;
	}
	free_list(current);
	return (str);
}
