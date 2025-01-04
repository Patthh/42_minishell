#include "../../include/minishell.h"

char	*expand_var(const char **pointer, t_program *minishell)
{
	char	*key;
	char	*value;

	key = env_name(pointer);
	if (!key)
		return (NULL);
	if (ft_strcmp(key, "?") == 0)
	{
		value = ft_itoa(minishell->status);
		free(key);
		return (value);
	}
	value = env_value(minishell, key);
	free(key);
	if (value)
		return (ft_strdup(value));
	else
		return (ft_strdup(""));
}

// expand the exit status "$?"
char	*expand_exit(t_program *minishell)
{
	char	*status;

	status = ft_itoa(minishell->status);
	return (status);
}

// expand a single character or environment variable
char	*expand_single(const char **string, t_program *minishell)
{
	char	*result;

	if (!string || !*string || !**string)
		return (NULL);
	if (**string == '$')
	{
		if (*(*string + 1) == '?')
		{
			(*string += 2);
			return (expand_exit(minishell));
		}
		else
			return (expand_var(string, minishell));
	}
	result = malloc(2);
	if (!result)
		return (NULL);
	result[0] = **string;
	result[1] = '\0';
	(*string)++;
	return (result);
}

// Expand environment variables within string
char	*quote_expand(char *string, t_program *minishell)
{
	const char	*pointer;
	char		*result;
	char		*temp;
	char		*new;

	result = ft_strdup("");
	temp = NULL;
	pointer = string;
	while (*pointer)
	{
		temp = expand_single(&pointer, minishell);
		if (temp)
		{
			new = ft_strjoin(result, temp);
			free (temp);
			free (result);
			result = new;
		}
	}
	return (result);
}
