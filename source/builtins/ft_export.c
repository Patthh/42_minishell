#include "../../include/minishell.h"

// extract key and value from export argument
// returns NULL if argument isn't in the correct format
static char	*export_argument(const char *argument, char **value)
{
	int		i;
	char	*key;

	i = 0;
	while (argument[i] && argument[i] != '=')
		i++;
	if (argument[i] != '=')
		return (NULL);
	key = ft_strndup(argument, i);
	*value = ft_strdup(argument + i + 1);
	return (key);
}

void	ft_export(t_command *command, t_program *minishell)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	while (command->arguments[i])
	{
		key = export_argument(command->arguments[i], &value);
		if (key && value)
		{
			add_env(minishell, key, value); // in ft_env
			free(key);
			free(value);
		}
		else
		{
			ft_putstr_fd("minishell: export: ", STDERR_FILENO);
			ft_putstr_fd(command->arguments[i], STDERR_FILENO);
			ft_putstr_fd("': not valid identifier\n", STDERR_FILENO);
			minishell->status = 1;
			return ;
		}
		i++;
	}
	minishell->status = 0;
}
