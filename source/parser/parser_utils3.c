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
