#include "../../include/minishell.h"

static int	export_valid(const char *string)
{
	if (!string || (!ft_isalpha(*string) && *string != '_'))
		return (0);
	while (*string)
	{
		if (!ft_isalnum(*string) && *string != '_')
			return (0);
		string++;
	}
	return (1);
}

static	void	export_error(const char *key)
{
	ft_putstr_fd("export:`", STDERR_FILENO);
	ft_putstr_fd((char *)key, STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

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

int	export_process(const char *argument, t_program *minishell)
{
	char	*key;
	char	*value;

	export_extract(argument, &key, &value);
	if (key && !export_valid(key))
	{
		export_error(key);
		free (value);
		free (key);
		return (1);
	}
	if (!key || !*key)
	{
		free (value);
		free (key);
		return (0);
	}
	export_update(minishell, key, value);
	free (key);
	return (0);
}

