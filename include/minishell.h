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

// typedef enum e_token {
// 	TOKEN_WORD,
// 	TOKEN_REDIRECT_IN,
// 	TOKEN_REDIRECT_OUT,
// 	TOKEN_REDIRECT_APPEND,
// 	TOKEN_REDIRECT_HEREDOC,
// 	TOKEN_PIPE,
// 	TOKEN_ENV_VAR,
// 	TOKEN_EXIT_STATUS,
// 	TOKEN_SPACE,
// 	TOKEN_EOF,
// } t_token_type;

// typedef struct s_token {
// 	t_token_type	type;
// 	char			*string;
// 	struct s_token	*next;

// } t_token;

#endif
