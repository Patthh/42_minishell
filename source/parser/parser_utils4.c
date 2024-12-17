#include "../../include/minishell.h"

// t_token	*parser_status(t_token *token, t_command *command, t_program *minishell)
// {
// 	char	status[16];

// 	ft_bzero(status, sizeof(status));
// 	ft_itoa(minishell->status, status);
// 	return (parser_word(token_word(status), command));
// }

// int	parser_sequence(t_token *tokens)
// {
// 	t_token	*token;

// 	token = tokens;
// 	while (token)
// 	{
// 		if (token->type == TKN_PIPE && (!token->next || token->next->type == TKN_PIPE))
// 		{
// 			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
// 			return (0);
// 		}
// 		if ((token->type == TKN_IN || token->type == TKN_OUT || token->type == TKN_RDA || token->type == TKN_RDH) && (!token->next || token->next->type != TKN_WORD))
// 		{
// 			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
// 			return (0);
// 		}
// 		token = token->next;
// 	}
// 	return (1);
// }
