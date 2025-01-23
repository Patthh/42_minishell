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
char	    *token_env_word(const char **input, t_program *minishell);
void			token_paranthesis(const char **input, t_token **head);
void			token_hash(const char **input, t_token **head);
void	    token_expand(const char	**input, char **result, t_program *minishell);
void			token_wildcard(const char **input, t_token **head);

char			*env_name(const char **input);
char			*env_value(t_program *minishell, const char *key);
void			env_token(t_token **head, t_program *minishell, const char *key);
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
t_token *parser_logical(t_token *token, t_command **command, t_pipeline *pipeline);\

// PIPELINE
int	validate_pipeline(t_pipeline *pipeline, t_program *minishell);
int	validate_command(t_command *command, t_program *minishell);
int	valid_cmd_name(const char *name);
int	validate_content(t_command *command, t_program *minishell);
int	validate_redirection_path(char *path, t_program *minishell);

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

int				update_pwd(t_program *minishell, const char *old_pwd);
char			*get_target(t_command *command, t_program *minishell);
char			*get_path(t_program *minishell, char *variable);
void			cd_error(char *path, char *message);

// EXECUTION
char			*find_command_path(char *cmd, t_program *minishell);
int				handle_redirections(t_command *command, t_program *minishell);
void			cleanup_redirections(t_command *command);
void			handle_execution_status(pid_t pid, t_program *minishell);
void			handle_execution_error(t_command *command, t_program *minishell,
		char *cmd_path, int error_type);
void			setup_pipes(t_pipeline *pipeline, int **pipe_fds);
void			close_pipes(t_pipeline *pipeline, int **pipe_fds);
void			setup_child_pipes(t_pipeline *pipeline, int **pipe_fds, int i);
void			execute_piped_command(t_command *command, t_program *minishell);
void			exec_err_exit(t_command *command, char *cmd_path);
void			execute_pipeline(t_pipeline *pipeline, t_program *minishell);
void			execute_command(t_command *command, t_program *minishell);
void			execute_builtin(t_command *command, t_program *minishell);
void			execute_in_child(char *cmd_path, t_command *command, t_program *minishell);


t_pipeline		*create_pipeline(void);
t_command		*create_command(void);
t_redirection	*create_redirection(const char *type, const char *filename, int quoted);



//HEREDOC
void			heredoc_read(t_redirection *heredoc, t_command *command, t_program *minishell);
int				setup_heredoc(t_command *command, t_program *minishell);
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
void	error_numeric(char *command, t_program *minishell);
void	error_identifier(char *identifier, t_program *minishell);
void	error_file_not_found_127(char *path, t_program *minishell);
void error_not_valid_identifier(char *command, t_program *minishell);
void	error_out_of_range(char *argument, t_program *minishell);
void	error_option(char *argument, t_program *minishell);

// env
void	init_env(t_program *minishell, char **envp);
void	add_env(t_program *minishell, const char *key, const char *value, int sign);

// SIGNAL
void	nl_handler(int signal);

// UTILS
void	ft_error(const char *message);
int setup_heredoc(t_command *command, t_program *minishell);
int		ft_isnumeric(const char *string);
int	ft_isspecial(char c);
int		ft_isredirect(char *argument);
int		ft_isredirect_token(t_token *token);
char	*token_join(char *s1, const char *s2);
void	token_regular(const char **input, char **result);

// TESTING
void	print_tokens(t_token *head);
void	print_pipeline(t_pipeline *pipeline);
void	print_redirection(t_redirection *redirection);


#endif
