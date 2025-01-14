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

// // // handle cases for empty values or quotes
// // static void	export_special(char **value)
// // {
// // 	char	*new_value;

// // 	if (*value == NULL)
// // 		return ;
// // 	else if (ft_strcmp(*value, "\"\"") == 0)
// // 	{
// // 		free(*value);
// // 		*value = ft_strdup("\\\"\\\"");
// // 	}
// // 	else if (ft_strchr(*value, '"') != NULL)
// // 	{
// // 		new_value = ft_strdup(*value);
// // 		free (*value);
// // 		*value = new_value;
// // 	}
// // }

// // validate/check variable name
// // return 0 if valid
// // return 1 if invalid
// // return 2 if empty
// static int	check_var_name(const char *name, char **error)
// {
// 	int	i;

// 	if (!name || !*name)
// 	{
// 		*error = ft_strdup("variable name cannot be empty");
// 		return (2);
// 	}
// 	if (!(ft_isalpha(name[0]) || name[0] == '_'))
// 	{
// 		*error = ft_strdup("variable name must begin with a 
// 				letter or underscore");
// 		return (1);
// 	}
// 	i = 1;
// 	while (name[i])
// 	{
// 		if (!(ft_isalnum(name[i]) || name[i] == '_'))
// 		{
// 			*error = ft_strdup("variable name can only contain 
// 				letters, digits, and underscores");
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// // extract variable name from argument
// // return string w variable name
// // NULL if allocation fails
// static char	*extract_var_name(const char *argument)
// {
// 	char	*equal;
// 	char	*name;

// 	if (!argument || !*argument)
// 		return (NULL);
// 	equal = ft_strchr(argument, '=');
// 	if (equal)
// 		name = ft_strndup(argument, equal - argument);
// 	else
// 		name = ft_strdup(argument);
// 	return (name);
// }

// int	export_validator(const char *argument, char **error)
// {
// 	char	*key;

// 	key = extract_var_name(argument);
// 	if (!key)
// 	{
// 		*error = ft_strdup("variable name cannot be empty");
// 		return (2);
// 	}
// 	if (check_var_name(key, error))
// 	{
// 		free(key);
// 		return (1);
// 	}
// 	free (key);
// 	return (0);
// }

// int	export_argument(const char *argument, t_program *minishell)
// {
// 	char	*message;
// 	int		valid;

// 	message = NULL;
// 	valid = export_validator(argument, &message);
// 	if (valid != 0)
// 	{
// 		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
// 		ft_putstr_fd((char *)argument, STDERR_FILENO);
// 		ft_putstr_fd("': ", STDERR_FILENO);
// 		ft_putstr_fd(message, STDERR_FILENO);
// 		ft_putstr_fd("\n", STDERR_FILENO);
// 		free (message);
// 		minishell->status = 1;
// 		return (1);
// 	}
// 	return (0);
// }
