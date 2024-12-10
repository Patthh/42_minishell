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

// int main (int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	t_program	minishell;
// 	t_token		*tokens;
// 	char		*input;

// 	init_minishell(&minishell, envp);
// 	while (!minishell.exit)
// 	{
// 		input = readline(PROMPT);
// 		if (input == NULL)
// 		{
// 			printf("\n");
// 			break ;
// 		}
// 		tokens = tokenizer(input);
// 		print_tokens(tokens);
// 		// parsing
// 		// execution
// 		if (ft_strcmp(input, "exit") == 0)
// 		{
// 			token_free_list(tokens);
// 			free (input);
// 			break ;
// 		}
// 		free(input);
// 		token_free_list(tokens);
// 	}
// 	free_minishell(&minishell);
// 	return (0);
// }
