#include "../../include/minishell.h"

// validates variable names
// checks for empty string or null
// first char must be letter or underscore
// rest of string must be alphanumeric of underscore
static int	export_valid(const char *string)
{
	if (!string || !*string)
		return (0);
	if (!ft_isalpha(*string) && *string != '_')
		return (0);
	string++;
	while (*string)
	{
		if (!ft_isalnum(*string) && *string != '_')
			return (0);
		string++;
	}
	return (1);
}

// prints error message for invalid identifiers
static	void	export_error(const char *key)
{
	ft_putstr_fd("export:`", STDERR_FILENO);
	ft_putstr_fd((char *)key, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

// updates and adds env with value expansion
// handle case with no value
// expand any variables in the value
static void	export_update(t_program *minishell, char *key, char *value)
{
	char	*expand;

	if (!value)
	{
		add_env(minishell, key, "");
		return ;
	}
	expand = quote_expand(value, minishell);
	free (value);
	if (!expand)
	{
		add_env(minishell, key, "");
		return ;
	}
	add_env(minishell, key, expand);
	free (expand);
}

// extracts key and value from argument
// handles special case where argument is "="
static void	export_extract(const char *argument, char **key, char **value)
{
	char	*equals;

	equals = ft_strchr(argument, '=');
	if (equals)
	{
		*key = ft_strndup(argument, equals - argument);
		*value = ft_strdup(equals + 1);
		return ;
	}
	*key = ft_strdup(argument);
	*value = NULL;
}

// extracts key and value from argument
// validates the key
// process if valid key
int	export_process(const char *argument, t_program *minishell)
{
	char	*key;
	char	*value;

	export_extract(argument, &key, &value);
	if (!export_valid(key))
	{
		export_error(key);
		minishell->status = 1;
		if (key)
			free (key);
		return (1);
	}
	if (key && *key)
	{
		export_update(minishell, key, value);
		minishell->status = 0;
	}
	if (key)
		free (key);
	return (0);
}
