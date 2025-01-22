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
	free(key);
	if (!value)
	{
		error_file_not_found(key, minishell);
		return (ft_strdup(""));
	}
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
	if (!string)
	{
		error_eof("", minishell);
		return (NULL);
	}
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

int	ft_isredirect_token(t_token *token)
{
	if (token->type == TKN_IN || token->type == TKN_OUT
		|| token->type == TKN_RDA || token->type == TKN_RDH)
		return (1);
	return (0);
}
