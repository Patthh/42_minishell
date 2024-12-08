#include "../../include/minishell.h"

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
