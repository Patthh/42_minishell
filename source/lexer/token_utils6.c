#include "../../include/minishell.h"

// extract env name
char	*env_name(const char **input)
{
	const char	*start;
	const char	*end;

	while (**input == '$')
		(*input)++;
	start = *input;
	end = start;
	while (*end && (ft_isalnum(*end) || *end == '_'))
		end++;
	if (start == end)
		return (NULL);
	return (ft_strndup(start, end - start));
}

// retrieve env value
char	*env_value(t_program *minishell, const char *key)
{
	t_env	*current;

	current = minishell->env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (getenv(key));
}

// create token for env
void	env_token(t_token **head, t_program *minishell, const char *key)
{
	char	*value;

	value = env_value(minishell, key);
	if (value)
		token_add(head, token_new(TKN_ENV, value));
}

char	*env_quote(t_program *minishell, const char *input)
{
	char	*key;
	char	*value;

	key = env_name(&input);
	if (!key)
		return (NULL);
	value = env_value(minishell, key);
	free(key);
	if (value)
		return (ft_strdup(value));
	else
		return (NULL);
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
