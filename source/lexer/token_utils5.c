#include "../../include/minishell.h"

static void	token_exit(const char **input, t_token **head, t_program *minishell)
{
	char	*exit;
	t_token	*status;

	(*input)++;
	if (**input == '?')
	{
		/* TO DO:
		* get exit status
		* handle edge cases (multiple $? in same command)
		* add error handling for status conversion
		*/
		exit = ft_itoa(minishell->status);
		if (exit)
		{
			status = token_new(TKN_STATUS, exit);
			token_add(head, status);
			free(exit);
		}
		(*input)++;
	}
}

char	*get_env_value(t_env *env_list, const char *key)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static void	token_env(const char **input, t_token **head, t_program *minishell)
{
	const char	*start;
	char		*env_var;
	char		*env_value;

	start = *input;
	while (**input && (ft_isalnum(**input) || **input == '_'))
		(*input)++;
	if (start == *input)
		return ;
	env_var = ft_strndup(start, *input - start);
	if (env_var)
	{
		env_value = NULL;
		if (minishell->env_list)
			env_value = get_env_value(minishell->env_list, env_var);
		if (!env_value)
			env_value = getenv(env_var);
		if (env_value)
			token_add(head, token_new(TKN_ENV, env_value));
		free(env_var);
	}
}

void	token_dollar(const char **input, t_token **head, t_program *minishell)
{
	(*input)++;
	while (**input && ft_isspace(**input))
		(*input)++;
	if (!**input)
	{
		token_add(head, token_new(TKN_WORD, "$"));
		return ;
	}
	if (**input == '?')
	{
		token_exit(input, head, minishell);
		return ;
	}
	if (ft_isalpha(**input) || **input == '_')
		token_env(input, head, minishell);
	else
	{
		token_add(head, token_new(TKN_WORD, "$"));
		return ;
	}
}
