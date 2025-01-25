#include "../include/minishell.h"

void	shell_exit(const char *input, t_token *tokens, t_program *minishell)
{
	int	exit_status;

	exit_status = minishell->status & 255;
	if (tokens)
		free_list(tokens);
	free((char *)input);
	free_shell(minishell);
	exit(exit_status);
}

	// print_tokens(tokens); // testing tokenizer
	// print_pipeline(pipeline); // testing parser
int	handle_input(char *input, t_program *minishell)
{
	t_token		*tokens;
	t_pipeline	*pipeline;

	if (!quote_tracker(input))
	{
		free(input);
		return (0);
	}
	if (input && *input)
		add_history(input);
	tokens = tokenizer(input, minishell);
	pipeline = parser(tokens, minishell);
	if (pipeline && !validate_pipeline(pipeline, minishell))
	{
		free_list(tokens);
		free_pipeline(pipeline);
		free(input);
		return (1);
	}
	execute_pipeline(pipeline, minishell);
	free_list(tokens);
	free_pipeline(pipeline);
	free(input);
	return (1);
}

void	run_shell(t_program *minishell)
{
	char	*input;
	char	*cwd;
	int		result;

	while (1)
	{
		cwd = getcwd(NULL, 0);
		if (cwd == NULL || access(cwd, F_OK) != 0)
			cwd_exit(cwd);
		free(cwd);
		signal(SIGINT, nl_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline(PROMPT);
		if (!input)
		{
			free_env (minishell->env_list);
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		result = handle_input(input, minishell);
		if (result < 0)
			break ;
	}
}

// initialize minishell's structure with default values
void	init_shell(t_program *program, char **envp)
{
	struct termios termios_p;

	tcgetattr(STDIN_FILENO, &termios_p);
	termios_p.c_iflag |= ICRNL;
	tcsetattr(STDIN_FILENO, TCSANOW, &termios_p);
	ft_memset(program, 0, sizeof(*program));
	program->envp = envp;
	program->status = 0;
	program->exit = 0;
	init_env(program, envp);
	update_shlvl(program);
}
