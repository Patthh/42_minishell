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
