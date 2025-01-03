#include "../include/minishell.h"

void	shell_exit(const char *input, t_token *tokens, t_program *minishell)
{
	if (tokens)
		free_list(tokens);
	free((char *)input);
	free_shell(minishell);
	exit(0);
}

int	handle_input(char *input, t_program *minishell)
{
	t_token		*tokens;
	t_pipeline	*pipeline;

	if (!quote_counter(input))
	{
		free(input);
		return (0);
	}
	if (input && *input)
		add_history(input);
	tokens = tokenizer(input, minishell);
	print_tokens(tokens); // testing tokenizer
	pipeline = parser(tokens, minishell);
	print_pipeline(pipeline); // testing parser
	// execution here
	if (ft_strcmp(input, "exit") == 0)
	{
		free_list(tokens);
		shell_exit(input, NULL, minishell);
		return (-1);
	}
	free_list(tokens);
	free_pipeline(pipeline);
	free(input);
	return (1);
}

void	run_shell(t_program *minishell)
{
	char	*input;
	int		result;

	while (1)
	{
		// if (handle_signal() < 0)
		// 	break ;
		input = readline("minishell$ ");
		if (!input)
			break ;
		result = handle_input(input, minishell);
		if (result < 0)
			break ;
	}
}

// initialize minishell's structure with default values
void	init_shell(t_program *program, char **envp)
{
	ft_memset(program, 0, sizeof(*program));
	program->envp = envp;
	program->status = 0;
	program->exit = 0;
}
