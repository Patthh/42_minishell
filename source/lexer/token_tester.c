#include "../../include/minishell.h"

void	print_tokens(t_token *head)
{
	t_token	*current;

	if (!head)
	{
		printf("Token list is empty.\n");
		return ;
	}
	current = head;
	while (current)
	{
		printf("Type: %d, Value: %s\n", current->type, current->value);
		current = current->next;
	}
}
