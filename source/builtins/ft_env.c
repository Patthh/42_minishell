#include "../../include/minishell.h"

int	ft_env(t_program *minishell)
{
	t_env	*current;

	current = minishell->env_list;
	while (current)
	{
		if (current->value)
		{
			write(STDOUT_FILENO, current->key, ft_strlen(current->key));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, current->value, ft_strlen(current->value));
			write(STDOUT_FILENO, "\n", 1);
		}
		current = current->next;
	}
	minishell->status = 0;
	return (0);
}

// void	add_env(t_program *minishell, const char *key, const char *value)
// {
// 	t_env	*new;

// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 		return ;
// 	new->key = ft_strdup(key);
// 	new->value = ft_strdup(value);
// 	new->next = minishell->env_list;
// 	minishell->env_list = new;
// }

// void	free_env(t_env *head)
// {
// 	t_env	*temp;

// 	while (head)
// 	{
// 		temp = head;
// 		head = head->next;
// 		free(temp->key);
// 		free(temp->value);
// 		free(temp);
// 	}
// }

// int	main(void)
// {
// 	t_program	minishell;

// 	minishell.env_list = NULL;
// 	add_env(&minishell, "PATH", "/bin:/usr/bin");
// 	add_env(&minishell, "HOME", "/home/user");
// 	add_env(&minishell, "USER", "user");
// 	ft_env(&minishell);
// 	free_env(minishell.env_list);
// 	return (0);
// }
