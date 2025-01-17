#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include <dirent.h> // opendir, readir
# include <limits.h>
# include "../libft/include/libft.h"

# define PROMPT "minishell$ "
# define TRUE 1
# define FALSE 0
# define EXIT_STATUS

// ENUMS
// Token types for lexer
typedef enum e_token
{
	TKN_IN,			// 0 <
	TKN_OUT,		// 1 >
	TKN_RDA,		// 2 >>
	TKN_RDH,		// 3 <<
	TKN_PIPE,		// 4 |
	TKN_ENV,		// 5 $VAR
	TKN_STATUS,		// 6 $?
	TKN_WHITESPACE, // 7
	TKN_EOF,		// 8
	TKN_BG,			// 9 &
	TKN_START,		// 10 (
	TKN_END,		// 11 )
	TKN_AND,		// 12 &&
	TKN_OR,			// 13 ||
	TKN_SINGLE,		// 14 single quote
	TKN_DOUBLE,		// 15 double quote
	TKN_WILDCARD,	// 16 *
	TKN_WORD,		// 17
	TKN_ASSIGN		// 18 =
}	t_token_type;

typedef enum e_logical
{
	LOG_AND,
	LOG_OR,
	LOG_NONE
} t_logical;

// // Add to your enum declarations
// typedef enum e_group_type
// {
// 	GROUP_COMMAND,	// Single command
// 	GROUP_PIPELINE	// Subpipeline/subshell
// }	t_group_type;

// // New group structure
// typedef struct s_group
// {
// 	t_group_type 			type; // Type of group (command or pipeline)
// 	union {
// 		t_command			*command; // Single command
// 		t_pipeline			*pipeline;  // Subpipeline for parentheses
// 	} content;
// 	t_logical				logical; // Logical operator following this group
// 	int						exit_status;
// 	struct s_group			*next;
// }	t_group;

// STRUCTURES
// token structure for lexer
typedef struct s_token
{
	t_token_type			type;
	char					*value;
	int						error;
	struct s_token			*next;
}	t_token;

// redirection structure
typedef struct s_redirection
{
	char					*type;
	char					*filename;
	int						quoted;
	char					*content;
	struct s_redirection	*next;
}	t_redirection;

// command structure to handle a single command
typedef struct s_command
{
	char					**arguments;
	char					*input_file;     // For < redirection
    char					*output_file;    // For > and >> redirection
    int						append_output;
	t_redirection			*input;
	t_redirection			*output;
	t_redirection			*append;
	t_redirection			*heredoc;
	int						fd_in;
	int						fd_out;
	int						is_builtin;
	int						exit_status;
	t_logical				logical;
	struct s_command		*next;
}	t_command;

// command structure to handle multiple commands
// if working, refractor it to use only groups
typedef struct s_pipeline
{
	t_command				**commands;
	int						cmd_count;
	// t_group					**groups; // Array of command groups
	// int						group_count; // Number of groups
	// int						is_subshell;
}	t_pipeline;

// environment variable structure
typedef struct s_env
{
	char					*key;
	char					*value;
	int						sign;
	struct s_env			*next;
}	t_env;

// main program structure
typedef struct s_program
{
	char					**envp;
	t_token					*token;
	t_command				*command;
	t_env					*env_list;
	int						status;
	int						exit;
}	t_program;

// FUNCTION PROTOTYPES

// SHELL
void			init_shell(t_program *program, char **envp);
void			run_shell(t_program *minishell);
int				handle_input(char *input, t_program *minishell);
void			shell_exit(const char *input, t_token *tokens, t_program *minishell);
int				quote_tracker(const char *input);
int				parentheses_tracker(const char *input);

// LEXER
t_token			*tokenizer(const char *input, t_program *minishell);
t_token			*token_new(t_token_type type, const char *value);
void			token_add(t_token **head, t_token *new_token);
void			token_redirector(const char **input, t_token **head);
void			token_operator(const char **input, t_token **head);
void			token_dollar(const char **input, t_token **head, t_program *minishell);
void			token_unquoted(const char **input, char **result, t_program *minishell);
void			token_double(const char **input, char **result, t_program *minishell);
void			token_single(const char **input, char **result);
void			token_assign(const char **input, t_token **head);
void			token_env(const char **input, t_token **head, t_program *shell);
void			token_word(const char **input, t_token **head, t_program *minishell);
void			token_extra(const char **input, t_token **head, t_program *minishell);
void			token_wildcard(const char **input, t_token **head);
char	*token_env_word(const char **input, t_program *minishell);
void			token_paranthesis(const char **input, t_token **head);
void			token_hash(const char **input, t_token **head);

char			*env_name(const char **input);
char			*env_value(t_program *minishell, const char *key);
void			env_word(const char **input, char **result, t_program *minishell);
t_env			*env_find(t_env *env_list, const char *key);

// PARSER
t_pipeline		*parser(t_token *tokens, t_program *minishell);
t_token			*parser_word(t_token *token, t_command *command);
t_token			*parser_token(t_token *token, t_command **command, t_program *minihell, t_pipeline *pipeline);
t_token			*parser_pipe(t_token *token, t_command **command, t_pipeline *pipeline);
t_token			*parser_redirection(t_token *token, t_command *command, t_program *minishell);
t_token			*parser_env(t_token *token, t_command *command, t_program *minishell);
t_token			*parser_status(t_token *token, t_program *minishell);
int				parser_argument(t_command *command, const char *value);
int				parser_builtin(const char *command);
int				parser_sequence(t_token *tokens, t_program *minishell);

// PARSER BONUS
t_token			*parser_wildcard(t_token *token, t_command *command);
t_token			*parser_logical(t_token *token, t_command **command, t_pipeline *pipeline);
// t_token		*parser_and(t_token *token, t_command **command, t_pipeline *pipeline);
// t_token		*parser_or(t_token *token, t_command **command, t_pipeline *pipeline);

// PIPELINE
int	validate_pipeline(t_pipeline *pipeline, t_program *minishell);
int	validate_command(t_command *command, t_program *minishell);
int	valid_cmd_name(const char *name);

// BUILTINS
int				ft_cd(t_command *command, t_program *minishell);
int				ft_echo(t_command *command, t_program *minishell);
int				ft_env(t_program *minishell);
int				ft_exit(t_command *command, t_program *minishell);
void			ft_export(t_command *command, t_program *minishell);
int				ft_pwd(t_program *minishell);
int				ft_unset(t_command *command, t_program *minishell);
int				ft_cd(t_command *command, t_program *minishell);

// BUILTINS UTILS
t_env			**export_sorting(t_program *minishell, int *size);
void 			export_update(t_program *minishell, char *key, char *value, int sign);
void			export_extract(const char *argument, char **key, char **value, int *sign);
int				export_process(const char *argument, t_program *minishell);
void			export_remove(t_program *minishell, const char *key);
void			export_argument(t_command *command, t_program *minishell);
t_env			**export_sorting(t_program *minishell, int *size);
void			export_error(const char *key, t_program *minishell);
int				export_valid(const char *string);
void			print_export(t_program *minishell);
void			free_key_value(char *key, char *value);

int				update_pwd(t_program *minishell);
char			*get_target(t_command *command, t_program *minishell);
char			*get_path(t_program *minishell, char *variable);
void			cd_error(char *path, char *message);

// EXECUTION
void			execute_pipeline(t_pipeline *pipeline, t_program *minishell);
void			execute_command(t_command *command, t_program *minishell);
void			execute_builtin(t_command *command, t_program *minishell);

t_pipeline		*create_pipeline(void);
t_command		*create_command(void);
t_redirection	*create_redirection(const char *type, const char *filename, int quoted);




void			heredoc_read(t_redirection *heredoc, t_command *command, t_program *minishell);
char			*quote_expand(char *string, t_program *minishell);
char			*expand_single(const char **string, t_program *minishell);
char			*expand_exit(t_program *minishell);
char			*expand_var(const char **pointer, t_program *minishell);


// MEMORY
void	init_env(t_program *minishell, char **envp);
void	free_shell(t_program *program);
void	free_token(t_token *token);
void	free_list(t_token *head);
void	free_redirection(t_redirection *redirection);
void	free_command(t_command *command);
void	free_pipeline(t_pipeline *pipeline);
void	free_args(char **strings);
void	free_env(t_env *head);
// void	free_parser(t_pipeline *pipeline);

// ERRORS
void	error_command(char *command, t_program *minishell);
void	error_eof(char *token, t_program *minishell);
void	error_syntax(char *message, t_program *minishell);
void	error_file_not_found(char *path, t_program *minishell);
void	error_arguments(char *command, t_program *minishell);
void	error_malloc(t_program *minishell);
void	error_unexpected_eof(t_program *minishell);
void	error_newline(t_program *minishell);
void	error_brace(char *brace, t_program *minishell);
void	error_not_found(char *command, t_program *minishell);
void	error_directory(char *command, t_program *minishell);
void	error_permission(char *command, t_program *minishell);

// env
void	init_env(t_program *minishell, char **envp);
void	add_env(t_program *minishell, const char *key, const char *value, int sign);

// SIGNAL
void	nl_handler(int signal);

// UTILS
void	ft_error(const char *message);
char	*token_join(char *s1, const char *s2);
void	token_regular(const char **input, char **result);
// void	ft_putstr_fd(char *s, int fd);
// int		ft_strcmp(const char *s1, const char *s2);
// void	*ft_memset(void *s, int c, size_t n);
// char	*ft_strdup(const char *s);
// char	*ft_strndup(const char *src, size_t n);
// char	*ft_strchr(const char *string, int c);
// int		ft_isalnum(int c);
// size_t	ft_strlen(const char *str);
// char	*ft_itoa(int n);
// int		ft_isdigit(int c);
// int		ft_isalpha(int c);
// int		ft_isascii(int c);
// int		ft_isspace(int c);
// char	*ft_strjoin(char const *s1, char const *s2);
// char	*ft_strjoin_char(const char *str, char c);
// char	*ft_strstr(const char *big, const char *little);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// int		ft_atoi(const char *nptr);
// long	ft_strtol(const char *string, char **end);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// char	**ft_split(char const *s, char c);
// void	*ft_calloc(size_t nmemb, size_t size);
// void	ft_bzero(void *s, size_t n);
// void	*ft_memcpy(void *dest, const void *src, size_t n);
// size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size);
// char	*ft_strtrim(char const *s1, char const *set);
// void	ft_sequence(const char *message);

// TESTING
void	print_tokens(t_token *head);
void	print_pipeline(t_pipeline *pipeline);


#endif
