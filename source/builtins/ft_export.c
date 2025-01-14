#include "../../include/minishell.h"

// handles without memory leaks
// export
// export a
// export a b c d e f g h
// export VAR=$USER
// export =
// export "="

// prints exported variables value in bash format
static void	export_print_value(const char *key, const char *value)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd((char *)key, STDOUT_FILENO);
	if (value)
	{
		ft_putstr_fd("=\"", STDOUT_FILENO);
		ft_putstr_fd((char *)value, STDOUT_FILENO);
		ft_putstr_fd("\"", STDOUT_FILENO);
	}
	else if (value && *value == '\0')
	{
		ft_putstr_fd("=\"\"", STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

// prints exported variable with or without its values
// depending on the sign and value
static void	export_print(const char *key, const char *value, int sign)
{
	if (sign)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd((char *)key, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else if (value == NULL)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd((char *)key, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
	{
		export_print_value(key, value);
	}
}

// prints exported variables in sorted order
static void	export_print_sorted(t_env **sorted, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		export_print(sorted[i]->key, sorted[i]->value, sorted[i]->sign);
		i++;
	}
}

// prints exported variables in the environement
// sorted alphabetically
static void	export_print(t_program *minishell)
{
	t_env	**sorted;
	int		size;

	sorted = export_sorting(minishell, &size);
	if (sorted)
	{
		export_print_sorted(minishell, size);
		free (sorted);
	}
	minishell->status = 0;
}

// process each argument passed to the export command
// updates the environment
static void	export_argument(t_command *command, t_program *minishell)
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
		export_print(minishell);
	else
		export_argument(command, minishell);
}
