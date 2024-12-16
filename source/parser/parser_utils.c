#include "../../include/minishell.h"

t_token	*parse_word(t_token *token, t_command *command)
{
	if (!parse_argument(command, token->value))
		ft_error("Parser: Failed to add argument\n");
	if (command->arguments[0] && parse_builtin(command->arguments[0]))
		command->is_builtin = 1;
	return (token->next);
}

int	parse_builtin(const char *command)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	int i;

	i = 0;
	while (builtins[i])
	{
		if (ft_strcmp(command, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}
