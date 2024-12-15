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
int match_pattern(const char *pattern, const char *filename) {
	while (*pattern && *filename) {
		if (*pattern == '*') {
			while (*pattern == '*')
				pattern++;
			if (*pattern == '\0')
				return 1;
			while (*filename) {
				if (match_pattern(pattern, filename))
					return 1;
				filename++;
			}
			return 0;
		} else if (*pattern != *filename) {
			return 0;
		}
		pattern++;
		filename++;
	}
	return (*pattern == '\0' && *filename == '\0');
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

// creates a TKN_WILDCARD for matching file and a TKN_WORD for the pattern
// find the extent of the pattern
// crate the extent from original input
// create pattern from origin input
void	token_wildcard(const char **input, t_token **head)
{
	DIR			*directory;
	const char	*start;
	char		*pattern;
	int			matched;

	start = *input;
	directory = NULL;
	pattern = NULL;
	while (**input == '*')
		(*input)++;
	while (**input != '\0' && **input != '*' && !ft_isspace(**input))
		(*input)++;
	pattern = ft_strndup(start, *input - start);
	directory = opendir(".");
	if (!directory)
	{
		perror("opendir");
		free (pattern);
		return ;
	}
	matched = add_wildcard(directory, pattern, head);
	if (!matched)
		token_add(head, token_new(TKN_WILDCARD, pattern));
	free (pattern);
}

