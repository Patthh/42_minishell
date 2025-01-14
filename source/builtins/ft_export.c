#include "../../include/minishell.h"

// handles without memory leaks
// export
// export a
// export b=
// export c=qwe
// export d="qwe"
// export e='qwe'
// export f=""
// export g=''
// export a b c d e f g h
// export VAR=$USER
// export =
// export "="

// extracts key and value from argument
// handles special case where argument is "="
void	export_extract(const char *argument, char **key,
	char **value, int *sign)
{
	char	*equals;

	equals = ft_strchr(argument, '=');
	if (equals)
	{
		*key = ft_strndup(argument, equals - argument);
		*value = ft_strdup(equals + 1);
		*sign = 0;
	}
	else
	{
		*key = ft_strdup(argument);
		*value = NULL;
		*sign = 1;
	}
}

// extracts key and value from argument
// validates the key
// process if valid key
int	export_process(const char *argument, t_program *minishell)
{
	char	*key;
	char	*value;
	int		sign;

	export_extract(argument, &key, &value, &sign);
	if (!export_valid(key))
	{
		export_error(key);
		minishell->status = 1;
		free_key_value(key, value);
		return (1);
	}
	if (key && *key)
	{
		export_update(minishell, key, value, sign);
		minishell->status = 0;
	}
	free_key_value(key, value);
	return (0);
}

// process each argument passed to the export command
// updates the environment
void	export_argument(t_command *command, t_program *minishell)
{
	int		i;
	char	*key;
	char	*value;
	int		sign;

	i = 1;
	while (command->arguments[i])
	{
		export_extract(command->arguments[i], &key, &value, &sign);
		export_process(command->arguments[i], minishell);
		free_key_value(key, value);
		i++;
	}
}

// handles export command
void	ft_export(t_command *command, t_program *minishell)
{
	if (!command->arguments[1])
		print_export(minishell);
	else
		export_argument(command, minishell);
}
