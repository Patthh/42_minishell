#include "../../include/minishell.h"

/*
 * tokenize the input string into a linked list of tokens
 * token_redirector -> token_utils.c
 * token_operator -> token_utils2.c
 * token_paranthesis -> token_utils3.c
 * token_quotes -> token_utils4.c
 * token_dollar -> token_utils5.c
 *
 * TO DO
 * wildcard
 * single token character tokens
 */
t_token	*tokenizer(const char *input, t_program *minishell)
{
	t_token		*head;

	head = NULL;
	if (!input)
		return (NULL);
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
			token_quotes(&input, &head, minishell);
		else if (*input == '$')
			token_dollar(&input, &head, minishell);
		// else if (*input == '*')
		// 	token_wildcard(&input, &head);
		else
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
		ft_error("Lexer: Failed to allocate memory for new token.\n");
	if (value)
	{
		token->value = ft_strdup(value);
		if (!token->value)
			free(token);
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

// extracts and creates a token for a word
t_token	*token_word(const char **input)
{
	const char	*start;
	char		*word;
	t_token		*token;

	start = *input;
	while (**input && (ft_isascii(**input)) && !ft_isspace(**input))
		(*input)++;
	word = ft_strndup(start, *input - start);
	token = token_new(TKN_WORD, word);
	free(word);
	return (token);
}
