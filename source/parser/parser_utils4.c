#include "../../include/minishell.h"

char	*expand_var(const char **pointer, t_program *minishell)
{
	char	*key;
	char	*value;

	key = env_name(pointer);
	if (!key)
	{
		error_syntax("$", minishell);
		return (ft_strdup("$"));
	}
	if (ft_strcmp(key, "?") == 0)
	{
		value = ft_itoa(minishell->status);
		free(key);
		return (value);
	}
	value = env_value(minishell, key);
	if (!value)
	{
		error_file_not_found(key, minishell);
		return (ft_strdup(""));
	}
	free(key);
	return (ft_strdup(value));
}

// expand the exit status "$?"
char	*expand_exit(t_program *minishell)
{
	char	*status;

	status = ft_itoa(minishell->status);
	if (!status)
	{
		error_malloc(minishell);
		return (NULL);
	}
	return (status);
}

// expand a single character or environment variable
char	*expand_single(const char **string, t_program *minishell)
{
	char	*result;

	if (!string || !*string || !**string)
	{
		error_eof("", minishell);
		return (NULL);
	}
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
	result = ft_strndup(*string, 1);
	if (!result)
		return (NULL);
	result[0] = **string;
	result[1] = '\0';
	(*string)++;
	return (result);
}

static char	*expand_append(char *result, char *expanded, t_program *minishell)
{
	char	*new;

	new = ft_strjoin(result, expanded);
	free(expanded);
	free(result);
	if (!new)
		error_malloc(minishell);
	return (new);
}

char	*quote_expand(char *string, t_program *minishell)
{
	char	*result;
	char	*expanded;

	if (!string)
		return (error_eof("", minishell), NULL);
	result = ft_strdup("");
	if (!result)
		error_malloc(minishell);
	while (*string)
	{
		expanded = expand_single((const char **)&string, minishell);
		if (!expanded)
		{
			free(result);
			return (NULL);
		}
		result = expand_append(result, expanded, minishell);
		if (!result)
			return (NULL);
	}
	return (result);
}
