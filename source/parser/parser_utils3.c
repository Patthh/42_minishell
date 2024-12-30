#include "../../include/minishell.h"

int	parser_builtin(const char *command)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int			i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(command, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	parser_argument(t_command *command, const char *value)
{
	int		count;
	char	**new;

	count = 0;
	while (command->arguments && command->arguments[count])
		count++;
	new = malloc(sizeof(char *) * (count + 2));
	if (!new)
		return (0);
	count = 0;
	while (command->arguments && command->arguments[count])
	{
		new[count] = command->arguments[count];
		count++;
	}
	free(command->arguments);
	new[count] = ft_strdup(value);
	new[count + 1] = NULL;
	command->arguments = new;
	return (1);
}

t_token	*parser_env(t_token *token, t_command *command, t_program *minishell)
{
	const char	*exp_pointer;
	char		*exp_value;

	exp_value = env_value(minishell, token->value);
	if (exp_value)
	{
		exp_pointer = exp_value;
		return (parser_word(token_word(&exp_pointer), command));
	}
	return (token->next);
}

t_token	*parser_status(t_token *token, t_program *minishell)
{
	char	*status;

	status = ft_itoa(minishell->status);
	if (!status)
		return (NULL);
	if (token->value)
		free(token->value);
	token->type = TKN_WORD;
	token->value = status;
	return (token);
}

int	parser_sequence(t_token *tokens)
{
	t_token	*token;

	token = tokens;
	while (token)
	{
		if (token->type == TKN_PIPE && (!token->next || token->next->type == TKN_PIPE))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", STDERR_FILENO);
			return (0);
		}
		if ((token->type == TKN_IN || token->type == TKN_OUT || token->type == TKN_RDA || token->type == TKN_RDH) && (!token->next || token->next->type != TKN_WORD))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", STDERR_FILENO);
			return (0);
		}
		token = token->next;
	}
	return (1);
}
