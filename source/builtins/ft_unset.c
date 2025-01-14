#include "../../include/minishell.h"

static void	unset_free(t_env *env)
{
	if (env)
	{
		free(env->key);
		free(env->value);
		free(env);
	}
}

// removes env from list based on key
static int	unset_remove(t_program *minishell, const char *key)
{
	t_env	*current;
	t_env	*previous;

	if (!key)
		return (0);
	current = minishell->env_list;
	previous = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				minishell->env_list = current->next;
			unset_free(current);
			return (0);
		}
		previous = current;
		current = current->next;
	}
	return (0);
}

// validates variable name
static int	unset_check(const char *name)
{
	if (!name || !*name)
		return (0);
	if (ft_isalnum(*name) || *name == '_')
	{
		name++;
		while (*name)
		{
			if (!(ft_isalnum(*name) || *name == '_'))
				return (0);
			name++;
		}
		return (1);
	}
	return (0);
}

// process a single argument
// check variable name
// remove variable from list
static int	unset_single(t_program *minishell, char *argument)
{
	if (!unset_check(argument))
	{
		ft_putstr_fd("unset: `", STDERR_FILENO);
		ft_putstr_fd("argument", STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	unset_remove(minishell, argument);
	return (0);
}

// unset command removes one or more env
int	ft_unset(t_command *command, t_program *minishell)
{
	int	i;
	int	status;

	if (!command->arguments || !command->arguments[1])
		return (0);
	i = 1;
	status = 0;
	while (command->arguments[i])
	{
		if (unset_single(minishell, command->arguments[i]) != 0)
			status = 1;
		i++;
	}
	minishell->status = status;
	return (status);
}
