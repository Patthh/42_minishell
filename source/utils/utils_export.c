#include "../../include/minishell.h"

// Count the number of environment variables in the list
static int	count_env(t_env *env_list)
{
	int		count;
	t_env	*current;

	if (!env_list)
		return (0);
	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

// Create an array of environment variables
static t_env	**array_env(t_env *env_list, int size)
{
	t_env	**array;
	t_env	*current;
	int		i;

	if (!env_list || size <= 0)
		return (NULL);
	array = malloc(sizeof(t_env *) * size);
	if (!array)
		return (NULL);
	current = env_list;
	i = 0;
	while (current && i < size)
	{
		if (!current->key || !current->value)
		{
			free(array);
			return (NULL);
		}
		array[i] = current;
		current = current->next;
		i++;
	}
	return (array);
}

// Sort the environment array using bubble sort
static void	sort_env(t_env **array, int size)
{
	t_env	*temp;
	int		i;
	int		j;

	if (!array || size <= 0)
		return ;
	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (array[j] == NULL || array[j + 1] == NULL)
				return ;
			if (ft_strcmp(array[j]->key, array[j + 1]->key))
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

// Main function to sort and return the environment array
t_env	**export_sorting(t_program *minishell, int *size)
{
	t_env	**array;

	if (!minishell || !size || !minishell->env_list)
		return (NULL);
	*size = count_env(minishell->env_list);
	if (*size <= 0)
		return (NULL);
	array = array_env(minishell->env_list, *size);
	if (!array)
		return (NULL);
	sort_env(array, *size);
	return (array);
}
