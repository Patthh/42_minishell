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
// opens a directory safely
DIR	*open_directory(const char *path)
{
	DIR	*directory = opendir(path);
	if (!directory)
		perror("opendir");
	return (directory);
}

// checks if a filename matches the wildcard pattern
int	match_pattern(const char *pattern, const char *filename)
{
	// TO DO
}

// adds wildcard tokens
int	add_wildcard(DIR *directory, const char *pattern, t_token **head)
{
	struct dirent	*entry;
	int				match;

	match = 0;
	if (!directory)
		return (match);
	while ((entry = readdir(directory)) != NULL)
	{
		if (entry->d_name[0] == '.')
			continue ;
		if (match_pattern(pattern, entry->d_name))
		{
			token_add(head, token_new(TKN_WILDCARD, entry->d_name));
			match = 1;
		}
	}
	closedir(directory);
	return (match);
}

void	single_wild(const char **input, t_token **head)
{
	char		*pattern;
	const char	*start;

	start = *input;
	pattern = ft_strndup(*input, **input - *start);
	token_add(head, token_new(TKN_WILDCARD, pattern));
	free (pattern);
}

// creates a TKN_WILDCARD for matching file and a TKN_WORD for the pattern
void	token_wildcard(const char **input, t_token **head)
{
	DIR			*directory;
	const char	*start;
	char		*pattern;
	int			match;

	start = *input;
	directory = NULL;
	pattern = NULL;
	match = 0;
	while (**input == '*')
		(*input)++;
	if (**input == '\0')
	{
		single_wild(input, head);
	}
	while (**input != '\0' && **input != '*' && !ft_isspace(**input))
		(*input)++;
	directory = open_directory(".");
	match = add_wildcard(directory, start, head);
	if (!match)
	{
		pattern = ft_strndup(start, *input - start);
		token_add(head, token_new(TKN_WILDCARD, pattern));
		free (pattern);
	}
}

