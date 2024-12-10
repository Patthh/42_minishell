#include "../../include/minishell.h"

/*
 * extra functions
 */

void	ft_error(const char *message)
{
	ft_putstr_fd((char *)message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	token_free(t_token *token)
{
	if (token)
	{
		if (token->value)
			free(token->value);
		free(token);
	}
}

void	token_free_list(t_token *head)
{
	t_token	*token;

	while (head)
	{
		token = head;
		head = head->next;
		token_free(token);
	}
}

// initialize minishell's structure with default values
void	init_minishell(t_program *program, char **envp)
{
	ft_memset(program, 0, sizeof(*program));
	program->envp = envp;
	program->status = 0;
	program->exit = 0;
}

void	free_minishell(t_program *program)
{
	if (program->token)
		token_free_list (program->token);
	if (program->command)
		free (program->command);
}
