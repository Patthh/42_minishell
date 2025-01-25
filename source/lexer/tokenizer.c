#include "../../include/minishell.h"

// tokenize the input string into a linked list of tokens
t_token	*tokenizer(const char *input, t_program *minishell)
{
	t_token	*head;

	head = NULL;
	if (!input || !*input)
		return (NULL);
	while (*input)
	{
		while (ft_isspace(*input))
			input++;
		if (!*input)
			break ;
		else if (*input == '#')
			break ;
		else if (*input == '<' || *input == '>')
			token_redirector(&input, &head);
		else if (*input == '|' || *input == '&')
			token_operator(&input, &head);
		else if (*input == '$')
			token_dollar(&input, &head, minishell);
		else
			token_extra(&input, &head, minishell);
	}
	return (head);
}

// handles the bonuses and word
void	token_extra(const char **input, t_token **head, t_program *minishell)
{
	if (**input == '*')
		token_wildcard(input, head, minishell);
	else
		token_word(input, head, minishell);
}
