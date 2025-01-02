#include "../../include/minishell.h"

// handles input and heredoc redirections
static void	token_input(const char **input, t_token **head)
{
	if (*(*input + 1) == '<')
	{
		token_add(head, token_new(TKN_RDH, "<<"));
		(*input) += 2;
	}
	else
	{
		token_add(head, token_new(TKN_IN, "<"));
		(*input)++;
	}
}

// handles output and append redirections
static void	token_output(const char **input, t_token **head)
{
	if (*(*input + 1) == '>')
	{
		token_add(head, token_new(TKN_RDA, ">>"));
		(*input) += 2;
	}
	else
	{
		token_add(head, token_new(TKN_OUT, ">"));
		(*input)++;
	}
}

// handles redirection tokens
void	token_redirector(const char **input, t_token **head)
{
	if (**input == '<')
		token_input(input, head);
	else if (**input == '>')
		token_output(input, head);
}

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
	*input = end;
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
