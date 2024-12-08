#include "../../include/minishell.h"

void	token_free(t_token *token)
{
	t_token	*current;
	while (token)
	{
		current = token;
		token = token->next;
		free(current->value);
		free(current);
	}
}
