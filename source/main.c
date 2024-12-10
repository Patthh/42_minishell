#include "../include/minishell.h"

void	ft_exit(char *input, t_token *tokens)
{
	token_free_list(tokens);
	free(input);
}

int	main(void)
{
	char		*input;
	t_token		*tokens;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (!quote_counter(input))
		{
			free (input);
			continue ;
		}
		tokens = tokenizer(input);
		print_tokens(tokens); // testing
		// parsing
		// execution
		if (ft_strcmp(input, "exit") == 0)
		{
			ft_exit(input, tokens);
			break ;
		}
		token_free_list(tokens);
		free(input);
	}
	return (0);
}
