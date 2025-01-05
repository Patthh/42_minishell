#include "../../include/minishell.h"

// Export a a=b b
// Result: a="b"
// b
// Export a=
// Result: a=""
// Export a='""'
// Result: a="\"\""

// prints formatted env
static void	export_print(t_env *env)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(env->key, STDOUT_FILENO);
	if (env->value)
	{
		if (ft_strchr(env->value, ' ') != NULL || ft_strchr(env->value, '"') != NULL)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		else
		{
			ft_putstr_fd("=", STDOUT_FILENO);
			ft_putstr_fd(env->value, STDOUT_FILENO);
		}
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}

// export_sorting in utils_builtins2.c
// export_process in utils_builtins3.c
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
			i = 0;
			while (i < size)
				export_print(sorted[i++]);
			free (sorted);
		}
		minishell->status = 0;
		return ;
	}
	minishell->status = 0;
	i = 1;
	while (command->arguments[i])
	{
		if (export_process(command->arguments[i], minishell))
			minishell->status = 1;
		i++;
	}
}
