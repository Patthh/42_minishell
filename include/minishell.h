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

typedef enum e_token {
	TOKEN_WORD,
	TOKEN_REDIRECT_IN,			// <
	TOKEN_REDIRECT_OUT,			// >
	TOKEN_REDIRECT_APPEND,		// >>
	TOKEN_REDIRECT_HEREDOC,		// <<
	TOKEN_PIPE,					// |
	TOKEN_ENV_VAR,				// $VAR
	TOKEN_EXIT_STATUS,			// $?
	TOKEN_SPACE,
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
	char					*file;
	struct s_redirection	*next;
} t_redirection;

// command structure to handle a single command
typedef struct s_command {
	t_redirection			*redirection;
	struct s_command		*next;
} t_command;

// command structure to handle multiple commands
typedef struct s_pipe {

} t_pipeline;

// structure to handle env
typedef struct s_env {
	char					*key;
	char					*value;
	struct s_env			*next;
} t_env;

typedef struct s_program {
	// int				std_out;
	// int				std_int;
	// int				std_err;
	t_token					*token;
	t_command				*command;
} t_program;

#endif
