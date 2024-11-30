#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

#define PROMPT "minishell$ "

// Function to get the current working directory for prompt
char* get_current_directory() {
	char* cwd = getcwd(NULL, 0);
	if (cwd == NULL) {
		perror("getcwd() error");
		return strdup("unknown");
	}
	return cwd;
}

// Main prompt loop
int main(int argc, char **argv, char **envp) {
	char *input;

	(void)argc;
	(void)argv;
	(void)envp;

	// Initialize readline
	rl_initialize();

	// Main command loop
	while (1) {
		// Get current directory for dynamic prompt
		char *cwd = get_current_directory();
		char prompt[1024];

		// Create dynamic prompt with current directory
		snprintf(prompt, sizeof(prompt), "%s:%s$ ", getenv("USER") ? getenv("USER") : "user", cwd);
		free(cwd);

		// Read input with readline
		input = readline(prompt);

		// Exit on Ctrl+D (NULL input)
		if (input == NULL) {
			printf("\nExiting minishell...\n");
			break;
		}

		// Skip empty lines
		if (strlen(input) == 0) {
			free(input);
			continue;
		}

		// Add to history
		add_history(input);

		// Basic exit command
		if (strcmp(input, "exit") == 0) {
			free(input);
			break;
		}

		// Process input (placeholder for future implementation)
		printf("You entered: %s\n", input);

		// Free input
		free(input);
	}

	return 0;
}
