#include "../../include/minishell.h"

char	*variable_expand(const char **input, t_token **head, t_program *minishell, const char **start)
{
	const char	*var_start = *input + 1;
	char		*name;
	char		*value;

	var_start = *input + 1;
	while (**input != '\0' && **input != '"' && (!ft_isalnum(**input) || **input == '_'))
		(*input)++;
	if (var_start == *input)
		return (NULL);
	name = ft_strndup(var_start, *input - var_start);
	value = get_env_value(minishell->env_list, name);
	if (!value)
		value = getenv(name);
	free(name);
	*start = *input;
	return (value);
}

void	token_wildcard(const char **input, t_token **head)
{
	if (**input == '*')
	{
		token_add(head, token_new(TKN_WILDCARD, "*"));
		(*input)++;
		return ;
	}
}
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
// void	handle_wildcard(const char **input, t_token **head)
// {
// 	DIR				*directory;
// 	const char		*token;
// 	struct dirent	*entry;

// 	directory = opendir(".");
// 	token = *input;
// 	if (!directory)
// 	{
// 		perror("opendir");
// 		return ;
// 	}
// 	while ((entry = readdir(directory)) != NULL)
// 	{
// 		if (ft_strcmp(token, "*") == 0 || ft_strstr(entry->d_name, token) != NULL)
// 			token_add(head, token_new(TKN_WILDCARD, entry->d_name));
// 	}
// 	closedir(directory);
// 	(*input)++;
// }
