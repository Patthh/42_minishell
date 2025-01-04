#include "../../include/minishell.h"

void	init_env(t_program *minishell, char **envp)
{
	int		i;
	char	*key;
	char	*value;
	char	*equals_sign;

	minishell->env_list = NULL;
	i = 0;
	while (envp[i])
	{
		equals_sign = ft_strchr(envp[i], '=');
		if (equals_sign)
		{
			key = ft_strndup(envp[i], equals_sign - envp[i]);
			value = ft_strdup(equals_sign + 1);
			add_env(minishell, key, value);
			free(key);
			free(value);
		}
		i++;
	}
}

int	ft_env(t_program *minishell)
{
	t_env	*current;

	current = minishell->env_list;
	while (current)
	{
		if (current->value)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	minishell->status = 0;
	return (0);
}

void	add_env(t_program *minishell, const char *key, const char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = minishell->env_list;
	minishell->env_list = new;
}

void	free_env(t_env *head)
{
	t_env	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}
