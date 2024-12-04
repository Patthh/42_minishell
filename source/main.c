#include "../include/minishell.h"

// initialize minishell's structure with default values
void	init_minishell(t_program *program, char **envp)
{
	// for the structure
	ft_memset(program, 0, sizeof(*program));

	// for specific fields
	program->envp = envp;
	program->status = 0;
	program->exit = 0;
}

void	free_minishell(t_program *program)
{
	if (program->token)
		free (program->token);
	if (program->command)
		free (program->command);
}

int	check_input(const char *string)
{
	while (*string)
	{
		if (isspace(*string))
			return (0);
		string++;
	}
	return (1);
}

int main (int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_program	minishell;
	char		*input;

	init_minishell(&minishell, envp);
	while (!minishell.exit)
	{
		input = readline(PROMPT);
		if (input == NULL)
		{
			printf("\n");
			break ;
		}
		if (ft_strcmp(input, "exit") == 0)
		{
			free (input);
			break ;
		}
		free (input);
	}
	free_minishell(&minishell);
	return (0);
}
