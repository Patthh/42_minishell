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
