#include "../../include/minishell.h"

/*
 * tokenize the input string into a linked list of tokens
 * token_redirector -> token_utils.c
 * token_operator -> token_utils2.c
 * token_paranthesis -> token_utils3.c
 *
 * TO DO
 * single and double quotes
 * env
 * $?
 * wildcard
 */
t_token	*tokenizer(const char *input)
{
	t_token		*head;

	head = NULL;
	while (*input)
	{
		if (isspace(*input))
			input++;
		else if (*input == '<' || *input == '>')
			token_redirector(&input, &head);
		else if (*input == '|' || *input == '&')
			token_operator(&input, &head);
		else if (*input == '(' || *input == ')')
			token_paranthesis(&input, &head);
		else if (*input == '\'' || *input == '"')
			token_quotes(&input, &head);
		token_add(&head, token_word(&input));
	}
	return (head);
}

// initializes a new token
t_token	*token_new(t_token_type type, const char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

// add token to the end of the token linked list
void	token_add(t_token **head, t_token *new_token)
{
	t_token	*current;

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

// extracts and creates a token for a word
t_token	*token_word(const char **input)
{
	const char	*start;

	start = *input;
	while (**input && ft_istokenable(**input))
		(*input)++;
	return (new_token(TKN_WORD, strndup(start, *input - start)));
}

// could do without this function
int	ft_istokenable(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '-' || c == '.' || c == '/')
		return (1);
	return (0);
}
