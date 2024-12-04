#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <string.h>
# include <errno.h>

# define PROMPT "minishell$ "
# define TRUE 1
# define FALSE 0

typedef enum e_token {
	TOKEN_WORD,
	TOKEN_REDIRECT_IN,			// <
	TOKEN_REDIRECT_OUT,			// >
	TOKEN_REDIRECT_APPEND,		// >>
	TOKEN_REDIRECT_HEREDOC,		// <<
	TOKEN_PIPE,					// |
	TOKEN_ENV_VAR,				// $VAR
	TOKEN_STATUS,				// $?
	TOKEN_WHITESPACE,
	TOKEN_EOF,
} t_token_type;

// token structure for lexer
typedef struct s_token {
	t_token_type			type;
	char					*value;
	struct s_token			*next;
} t_token;

// redirection structure
typedef struct s_redirection {
	char					*type; // IN, OUT, APPEND, HEREDOC
	char					*filename;
	struct s_redirection	*next;
} t_redirection;

// command structure to handle a single command
typedef struct s_command {
	char					**arguments;
	t_redirection			*input;
	t_redirection			*output;
	int						fd_in;
	int						fd_out;
	int						is_builtin;
	struct s_command		*next;
} t_command;

// command structure to handle multiple commands
typedef struct s_pipeline {
	t_command				**commands; // array of commands
	int						cmd_count;
} t_pipeline;

// structure to handle env
typedef struct s_env {
	char					*key;
	char					*value;
	struct s_env			*next;
} t_env;

typedef struct s_program {
	char					**envp; // array of environment variables
	t_token					*token;
	t_command				*command;
	t_env					*env_list;
	int						status;
	int						exit;
} t_program;

#endif
