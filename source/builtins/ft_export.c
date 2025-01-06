#include "../../include/minishell.h"

// extracts key and value from argument
static void	export_extract(const char *argument, char **key, char **value)
{
	char	*equals;

	equals = ft_strchr(argument, '=');
	if (equals)
	{
		*key = ft_strndup(argument, equals - argument);
		*value = ft_strdup(equals + 1);
	}
	else
	{
		*key = ft_strdup(argument);
		*value = NULL;
	}
}

static int	export_process(const char *argument, t_program *minishell)
{
	char	*key;
	char	*value;
	char	*expand;

	export_extract(argument, &key, &value);
	if (value)
	{
		expand = quote_expand(value, minishell);
		free(value);
		if (expand)
		{
			add_env(minishell, key, expand);
			free(expand);
		}
		else
			add_env(minishell, key, "");
	}
	else
		add_env(minishell, key, "");
	free(key);
	return (0);
}

// prints formatted env
static void	export_print(t_env *env)
{
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	ft_putstr_fd(env->key, STDOUT_FILENO);
	if (env->value && *env->value != '\0')
	{
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putstr_fd(env->value, STDOUT_FILENO);
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
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
			i = 0;
			while (i < size)
				export_print(sorted[i++]);
			free (sorted);
		}
		minishell->status = 0;
		return ;
	}
	i = 1;
	while (command->arguments[i])
	{
		export_process(command->arguments[i], minishell);
		i++;
	}
}
