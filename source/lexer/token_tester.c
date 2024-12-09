#include "../../include/minishell.h"

void	print_tokens(t_token *head)
{
	t_token	*current;

	current = head;
	while (current)
	{
		printf("Token Type: %d, Value: '%s'\n", current->type, current->value);
		current = current->next;
	}
}

int main(void)
{
	
}
