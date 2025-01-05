#include "../../include/minishell.h"

// count n env in list
static int	count_env(t_env *env_list)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

// creates an arrray of env
static t_env	**array_env(t_env *env_list, int size)
{
	int		i;
	t_env	**array;
	t_env	*current;

	i = 0;
	current = env_list;
	array = malloc(sizeof(t_env *) * size);
	if (!array)
		return (NULL);
	while (current)
	{
		array[i++] = current;
		current = current->next;
	}
	return (array);
}

// sorts env array w bubble sort
// must be in ascending order
static void	sort_env(t_env **array, int size)
{
	int		i;
	int		j;
	t_env	*temp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(array[j]->key, array[j + 1]->key) > 0)
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

t_env	**export_sorting(t_program *minishell, int *size)
{
	t_env	**array;

	*size = count_env(minishell->env_list);
	if (*size == 0)
		return (NULL);
	array = array_env(minishell->env_list, *size);
	if (!array)
		return (NULL);
	sort_env(array, *size);
	return (array);
}

// int main(void)
// {
// 	int			i;
// 	int			size;
// 	t_program 	minishell;
// 	t_env		**sorted;

// 	t_env env1 = {.key = "PATH", .next = NULL};
// 	t_env env2 = {.key = "HOME", .next = NULL};
// 	t_env env3 = {.key = "USER", .next = NULL};

// 	env1.next = &env2;
// 	env2.next = &env3;
// 	minishell.env_list = &env1;
// 	sorted = export_sorting(&minishell, &size);
// 	if (sorted)
// 	{
// 		i = 0;
// 		while (i < size)
// 		{
// 			printf("%s\n", sorted[i]->key);
// 			i++;
// 		}
// 		free(sorted);
// 	}
// 	return 0;
// }
