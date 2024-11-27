#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	char *rl;
	while (1)
	{
		rl = readline("minishell >");
		if (strcmp(rl, "exit") == 0)
		{
			free (rl);
			break ;
		}
	}
	printf("%s\n", rl);
	free (rl);
	return (0);
}
