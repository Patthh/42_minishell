#include "../../include/minishell.h"

void	init_env(t_program *minishell, char **envp)
{
	int		i;
	char	*key;
	char	*value;
	char	*sign;

	minishell->env_list = NULL;
	i = 0;
	while (envp[i])
	{
		sign = ft_strchr(envp[i], '=');
		if (sign)
		{
			key = ft_strndup(envp[i], sign - envp[i]);
			value = ft_strdup(sign + 1);
			add_env(minishell, key, value, 0);
			free(key);
			free(value);
		}
		i++;
	}
}

void	add_env(t_program *minishell, const char *key, const char *value, int sign)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return ;
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->sign = sign;
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

t_env	*env_find(t_env *env_list, const char *key)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
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
