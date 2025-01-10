#include "../../include/minishell.h"

// handles without memory leaks
// export
// export a
// export a b c d e f g h
// export VAR=$USER
// export =
// export "="


// prints formatted env
static void	export_print(const char *key, const char *value)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd((char *)key, STDOUT_FILENO);
	if (value && *value != '\0')
	{
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd((char *)value, STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

static void	export_print_sorted(t_env **sorted, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		export_print(sorted[i]->key, sorted[i]->value);
		i++;
	}
}

void	ft_export(t_command *command, t_program *minishell)
{
	t_env	**sorted;
	int		size;
	int		i;

	if (!command->arguments[1])
	{
		sorted = export_sorting(minishell, &size);
		if (sorted)
		{
			export_print_sorted(sorted, size);
			free (sorted);
		}
		minishell->status = 0;
		return ;
	}
	i = 1;
	while (command->arguments[i])
		export_process(command->arguments[i++], minishell);
}
