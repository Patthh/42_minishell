#include "../../include/minishell.h"

static void word_single(const char **input, char **result);
static void	handle_env_var(const char **input, char **result, t_program *minishell);
static void	handle_regular_char(const char **input, char **result);
static char *word_join(char *s1, const char *s2);
static void word_unquoted(const char **input, char **result, t_program *minishell);
static void word_double(const char **input, char **result, t_program *minishell);
static void word_single(const char **input, char **result);

// initializes a new token
t_token *token_new(t_token_type type, const char *value)
{
	t_token *token;

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
void token_add(t_token **head, t_token *new_token)
{
	t_token *current;

	if (!new_token)
		return;
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


// Helper function to handle environment variable expansion
static void	handle_env_var(const char **input, char **result, t_program *minishell)
{
	char *key;
	char *value;

	(*input)++; // Skip the '$'
	if (**input && (ft_isalnum(**input) || **input == '_' || **input == '?'))
	{
		key = env_name(input); // Extract the environment variable name
		value = env_value(minishell, key); // Get the value of the environment variable
		if (value)
			*result = word_join(*result, value); // Append the value to the result
		free(key); // Free the key after use
	}
	else
	{
		*result = word_join(*result, "$"); // Append a literal '$' to the result
	}
}

// Helper function to handle regular characters
static void	handle_regular_char(const char **input, char **result)
{
	char current[2];

	current[0] = **input; // Store the current character
	current[1] = '\0'; // Null-terminate the string
	*result = word_join(*result, current); // Append the character to the result
	(*input)++; // Move to the next character
}

// helper to join strings and handle memory
static char *word_join(char *s1, const char *s2)
{
	char *temp;

	if (!s1)
		return (ft_strdup(s2));
	temp = ft_strjoin(s1, s2);
	free(s1);
	return (temp);
}

static void word_unquoted(const char **input, char **result, t_program *minishell)
{
	while (**input && !ft_isspace(**input) && **input != '\'' && **input != '"')
	{
		if (**input == '$')
			handle_env_var(input, result, minishell);
		else
			handle_regular_char(input, result);
	}
}

// Process content within double quotes and handle variable expansion
static void word_double(const char **input, char **result, t_program *minishell)
{
	(*input)++; // Skip the opening double quote
	while (**input && **input != '"')
	{
		if (**input == '$')
			handle_env_var(input, result, minishell); // Handle environment variable
		else
			handle_regular_char(input, result); // Handle regular character
	}
	if (**input == '"')
		(*input)++; // Skip the closing double quote
}

// Handle word with quotes
static void handle_word(const char **input, t_token **head, t_program *minishell)
{
	char *result;

	result = NULL;
	while (**input && !ft_isspace(**input))
	{
		if (**input == '\'')
			word_single(input, &result);
		else if (**input == '"')
			word_double(input, &result, minishell);
		else
			word_unquoted(input, &result, minishell);
	}
	if (result)
	{
		token_add(head, token_new(TKN_WORD, result));
		free(result);
	}
}

// process content within single quotes
// treat as literal
static void word_single(const char **input, char **result)
{
	const char *start;
	char *content;

	(*input)++;  // Skip the opening quote
	start = *input;
	while (**input && **input != '\'')
		(*input)++;
	if (**input)
	{
		content = ft_strndup(start, *input - start);
		*result = word_join(*result, content);
		free(content);
		(*input)++;
	}
}

// tokenize the input string into a linked list of tokens
t_token *tokenizer(const char *input, t_program *minishell)
{
	t_token *head;

	head = NULL;
	if (!input || !*input)
		return (NULL);
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (!*input)
			break;
		else if (*input == '<' || *input == '>')
			token_redirector(&input, &head);
		else if (*input == '|' || *input == '&')
			token_operator(&input, &head);
		else if (*input == '*')
			token_wildcard(&input, &head);
		else
			handle_word(&input, &head, minishell);
	}
	return (head);
}

void token_extra(const char **input, t_token **head, t_program *minishell)
{
	if (**input == '*')
		token_wildcard(input, head);
	// else if (**input == '(' || **input == ')')
	//     token_paranthesis(input, head);
	else
		handle_word(input, head, minishell);
}
