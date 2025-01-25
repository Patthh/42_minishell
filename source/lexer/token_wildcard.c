/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:44:11 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:44:12 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// extract prefix before first wildcard
static char	*wildcard_prefix(const char *input)
{
	const char	*star;
	char		*prefix;

	if (!input)
		return (NULL);
	star = ft_strchr(input, '*');
	prefix = NULL;
	if (star)
		prefix = ft_strndup(input, star - input);
	else
		prefix = ft_strdup(input);
	return (prefix);
}

// extract suffix after last wildcard
static char	*wildcard_suffix(const char *input)
{
	const char	*star;
	char		*suffix;

	if (!input)
		return (NULL);
	star = ft_strrchr(input, '*');
	if (star)
		suffix = ft_strdup(star + 1);
	else
		suffix = NULL;
	return (suffix);
}

static char	*wildcard_pattern(const char *input)
{
	char	*pattern;
	char	*prefix;
	char	*suffix;
	char	*temp;

	prefix = wildcard_prefix(input);
	suffix = wildcard_suffix(input);
	if (!prefix && !suffix)
		return (NULL);
	if (prefix && suffix)
	{
		temp = ft_strjoin(prefix, "*");
		pattern = ft_strjoin(temp, suffix);
		free (temp);
	}
	else if (prefix)
		pattern = ft_strjoin(prefix, "*");
	else
		pattern = ft_strjoin("*", suffix);
	free (prefix);
	free (suffix);
	return (pattern);
}

static int	wildcard_directory(char *pattern, t_token **head,
	t_program *minishell)
{
	DIR	*directory;
	int	matched;

	if (!pattern)
		return (0);
	directory = opendir(".");
	if (!directory)
	{
		perror("opendir");
		return (0);
	}
	matched = add_wildcard(directory, pattern, head);
	closedir(directory);
	if (matched == -1)
	{
		error_no_match(pattern, minishell);
		return (-1);
	}
	if (!matched)
		token_add(head, token_new(TKN_WILDCARD, pattern));
	return (matched);
}

int	token_wildcard(const char **input, t_token **head, t_program *minishell)
{
	char		*pattern;

	pattern = wildcard_pattern(*input);
	if (!pattern)
		return (0);
	while (**input && (**input == '*' || !ft_isspace(**input)))
		(*input)++;
	if (wildcard_directory(pattern, head, minishell) == -1)
	{
		free (pattern);
		if (*head)
		{
			free_list(*head);
			*head = NULL;
		}
		return (-1);
	}
	free (pattern);
	return (0);
}
