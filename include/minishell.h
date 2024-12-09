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

// check the token type number of the symbols
// grep 'TKN_' include/minishell.h | awk '{print NR-1, $1}'
typedef enum e_token {
	TKN_IN,			// <
	TKN_OUT,		// >
	TKN_RDA,		// >>
	TKN_RDH,		// <<
	TKN_PIPE,		// |
	TKN_ENV,		// $VAR
	TKN_STATUS,		// $?
	TKN_WHITESPACE,
	TKN_EOF,
	TKN_BG,			// &
	TKN_START,		// (
	TKN_END,		// )
	TKN_AND,		// &&
	TKN_OR,			// ||
	TKN_SINGLE,		// single quote
	TKN_DOUBLE,		// double quote
	TKN_WILDCARD,	// *
	TKN_WORD,
} t_token_type;

// token structure for lexer
typedef struct s_token {
	t_token_type			type;
	char					*value;
	int						error;
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

// MAIN
int	check_input(const char *string);
void	init_minishell(t_program *program, char **envp);
void	free_minishell(t_program *program);

// LEXER
// tokenizer
t_token	*tokenizer(const char *input);
t_token	*token_new(t_token_type type, const char *value);
void	token_add(t_token **head, t_token *new_token);
t_token	*token_word(const char **input);
t_token	*token_word(const char **input);

// lexer utils
void	token_redirector(const char **input, t_token **head);
void	token_operator(const char **input, t_token **head);
void	token_paranthesis(const char **input, t_token **head);
void	token_quotes(const char **input, t_token **head);
void	token_free(t_token *token);
void	token_free_list(t_token *head);

// lexer testing
void	print_tokens(t_token *head);

// utils
void	ft_error(const char *message);
void	ft_putstr_fd(char *s, int fd);

int		ft_strcmp(const char *s1, const char *s2);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strdup(const char *s);
char	*ft_strndup(const char *src, size_t n);
char	*ft_strchr(const char *string, int c);
int		ft_isalnum(int c);
size_t	ft_strlen(const char *str);

#endif
