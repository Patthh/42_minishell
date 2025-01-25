/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aomont <aomont@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:44:01 by aomont            #+#    #+#             */
/*   Updated: 2025/01/25 18:44:02 by aomont           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
 * use opendir to open the current directory
 * use readdir to read each entry in the directory
 * implement a simple matching function for filenames
 * create token for matching filenames
 *
 * opendir - opens a directory
 * readdir - reads a directory, uses struct dirent
 * perror - prints a system error message
 */
// checks if a filename matches the wildcard pattern
// skip consecutive *
// if rest of pattern empty, match
// parse to match remain pattern with rest of filename
int	match_pattern(const char *pattern, const char *filename)
{
	if (!pattern || !filename)
		return (0);
	while (*pattern && *filename)
	{
		if (*pattern == '*')
		{
			while (*pattern == '*')
				pattern++;
			if (*pattern == '\0')
				return (1);
			while (*filename)
			{
				if (match_pattern(pattern, filename))
					return (1);
				filename++;
			}
			return (0);
		}
		else if (*pattern != *filename)
			return (0);
		pattern++;
		filename++;
	}
	return (*pattern == '\0' && *filename == '\0');
}

// adds wildcard tokens
// Add wildcard tokens
int	add_wildcard(DIR *directory, const char *pattern, t_token **head)
{
	struct dirent	*entry;
	int				match;

	match = 0;
	entry = readdir(directory);
	while (entry != NULL)
	{
		if (entry->d_name[0] == '.' && pattern[0] != '.')
		{
			entry = readdir(directory);
			continue ;
		}
		if (match_pattern(pattern, entry->d_name))
		{
			token_add(head, token_new(TKN_WILDCARD, entry->d_name));
			match = 1;
		}
		entry = readdir(directory);
	}
	if (!match)
		return (-1);
	return (match);
}
