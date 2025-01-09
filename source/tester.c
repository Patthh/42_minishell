#include "../include/minishell.h"

void	print_tokens(t_token *head)
{
	t_token	*current;

	// if (!head)
	// {
	// 	printf("Token list is empty.\n");
	// 	return ;
	// }
	current = head;
	while (current)
	{
		printf("Type: %d, Value: %s\n", current->type, current->value);
		current = current->next;
	}
}


// Simple and basic print_pipeline function
void print_pipeline(t_pipeline *pipeline)
{
    t_command *command;
    t_redirection *curr;
    int i;
    int j;

    if (!pipeline)
    {
        printf("Pipeline: nothing in there\n");
        return;
    }
    i = 0;
    while (i < pipeline->cmd_count)
    {
        command = pipeline->commands[i];
        printf("Command %d:\n", i + 1);
        j = 0;
        while (command->arguments && command->arguments[j])
        {
            printf(" Arg %d: %s\n", j + 1, command->arguments[j]);
            j++;
        }
        if (command->input)
        {
            printf(" Input:");
            curr = command->input;
            while (curr)
            {
                printf(" %s", curr->filename);
                curr = curr->next;
                if (curr)
                    printf(" ->");
            }
            printf("\n");
        }
        if (command->output)
            printf(" Output: %s\n", command->output->filename);
        if (command->append)
            printf(" Append: %s\n", command->append->filename);
        if (command->heredoc)
        {
            printf(" Heredoc:");
            curr = command->heredoc;
            while (curr)
            {
                printf(" %s", curr->filename);
                curr = curr->next;
                if (curr)
                    printf(" ->");
            }
            printf("\n");
        }

        // Print the logical operator status
        printf(" Logical Operator: ");
        if (command->logical == LOG_AND)
            printf("&&\n");
        else if (command->logical == LOG_OR)
            printf("||\n");
        else
            printf("None\n");

        i++;
    }
}
