#include "../../include/minishell.h"

void	free_key_value(char *key, char *value)
{
	if (key)
		free (key);
	if (value)
		free (value);
}

// validates variable names
// checks for empty string or null
// first char must be letter or underscore
// rest of string must be alphanumeric of underscore
int	export_valid(const char *string)
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
void	export_error(const char *key, t_program *minishell)
{
	if (*key == '\0')
		ft_putstr_fd("minishell: export: `=': not a valid identifier\n",
			STDERR_FILENO);
	else
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd((char *)key, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	}
	minishell->status = 1;
}

// updates and adds env with value expansion
// handle case with no value
// expand any variables in the value
void	export_update(t_program *minishell, char *key, char *value, int sign)
{
	char	*expand;

	export_remove(minishell, key);
	if (!value || ft_strcmp(value, "") == 0)
	{
		add_env(minishell, key, "", sign);
		return ;
	}
	expand = quote_expand(value, minishell);
	if (!expand)
	{
		add_env(minishell, key, "", sign);
		return ;
	}
	add_env(minishell, key, expand, sign);
	free(expand);
}
