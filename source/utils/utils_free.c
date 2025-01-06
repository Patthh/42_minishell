#include "../../include/minishell.h"

void	free_token(t_token *token)
{
	if (token)
	{
		if (token->value)
		{
			free(token->value);
			token->value = NULL;
		}
		free(token);
	}
}

void	free_list(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
}

void	free_shell(t_program *minishell)
{
	if (minishell->token)
	{
		free_list(minishell->token);
		minishell->token = NULL;
	}
}

void	free_args(char **strings)
{
	int	i;

	i = 0;
	while (strings[i] != NULL)
	{
		free(strings[i]);
		i++;
	}
	free (strings);
}
