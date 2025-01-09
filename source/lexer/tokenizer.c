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

static void	handle_word(const char **input, t_token **head, int *flag)
{
	const char	*start;
	char		*word;

	start = *input;
	while (**input && (!isspace(**input) || *flag))
	{
		if (**input == '=')
			*flag = 1;
		else if (isspace(**input) && !*flag)
			break ;
		(*input)++;
	}
	word = ft_strndup(start, *input - start);
	token_add(head, token_new(TKN_WORD, word));
	free(word);
	if (isspace(**input))
		*flag = 0;
}

// tokenize the input string into a linked list of tokens
t_token	*tokenizer(const char *input, t_program *minishell)
{
	t_token		*head;
	int			flag;

	head = NULL;
	flag = 0;
	if (!input || !*input)
		return (NULL);
	while (*input)
	{
		while (ft_isspace(*input) && !flag)
			input++;
		if (!*input)
			break ;
		else if (*input == '<' || *input == '>')
			token_redirector(&input, &head);
		else if (*input == '|' || *input == '&')
			token_operator(&input, &head);
		else if (*input == '\'' || *input == '"')
			token_quotes(&input, &head, minishell);
		else if (*input == '$')
			token_dollar(&input, &head, minishell);
		else
			token_extra(&input, &head, flag);
	}
	return (head);
}

void	token_extra(const char **input, t_token **head, int flag)
{
	if (**input == '*')
		token_wildcard(input, head);
	// else if (**input == '(' || **input == ')')
	// 	token_paranthesis(input, head);
	else
		handle_word(input, head, &flag);
}
