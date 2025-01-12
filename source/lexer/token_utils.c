#include "../../include/minishell.h"

// initializes a new token
t_token	*token_new(t_token_type type, const char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_error("Lexer: Failed to allocate memory for new token.\n");
	token->type = type;
	if (value)
	{
		token->value = ft_strdup(value);
		if (!token->value)
			ft_error("Lexer: failed to allocation memory for token value\n");
	}
	else
		token->value = NULL;
	token->type = type;
	token->next = NULL;
	return (token);
}

// add token to the end of the token linked list
void	token_add(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!new_token)
		return ;
	if (!*head)
		*head = new_token;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_token;
	}
}

// handle word token
void	token_word(const char **input, t_token **head, t_program *minishell)
{
	char	*result;

	result = NULL;
	while (**input && !ft_isspace(**input))
	{
		if (**input == '\'')
			token_single(input, &result);
		else if (**input == '"')
			token_double(input, &result, minishell);
		else
			token_unquoted(input, &result, minishell);
	}
	if (**input == '=')
		token_assign(input, head);
	else
	{
		if (result)
		{
			token_add(head, token_new(TKN_WORD, result));
			free(result);
		}
	}
}
