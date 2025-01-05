#include "../../include/minishell.h"

// handle errors for invalid export arguments
static int	export_error(const char *argument, t_program *minishell)
{
	int	i;

	if (!argument || !*argument || (!ft_isalpha(*argument) && *argument != '_'))
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd((char *)argument, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		minishell->status = 1;
		return (1);
	}
	i = 1;
	while (argument[i] && argument[i] != '=')
	{
		if (!ft_isalnum(argument[i]) && argument[i] != '_')
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd((char *)argument, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			minishell->status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

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

// handle cases for empty values or quotes
static void	export_special(char **value)
{
	char	*new_value;

	if (*value == NULL)
		*value = ft_strdup("");
	else if (ft_strcmp(*value, "\"\"") == 0)
	{
		free(*value);
		*value = ft_strdup("\\\"\\\"");
	}
	else if (ft_strchr(*value, '"') != NULL)
	{
		new_value = ft_strdup(*value);
		free (*value);
		*value = new_value;
	}
}

// check key name
static int	export_valid(const char *key)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (0);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// adds or updates env
static int	export_update(t_program *minishell, char *key, char *value)
{
	char	*new_value;

	new_value = NULL;
	if (value)
		new_value = ft_strdup(value);
	if (new_value)
		free (new_value);
	export_special(&new_value);
	if (export_valid(key))
		add_env(minishell, key, new_value);
	else
	{
		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
		ft_putstr_fd(key, STDERR_FILENO);
		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
		minishell->status = 1;
	}
	free(key);
	if (new_value)
		free(new_value);
	return (0);
}

// process each export argument
// int	export_process(const char *argument, t_program *minishell)
// {
// 	char	*key;
// 	char	*value;

// 	if (export_error(argument, minishell))
// 		return (1);
// 	export_extract(argument, &key, &value);
// 	if (!key)
// 		return (1);
// 	if (export_error(key, minishell))
// 	{
// 		free (key);
// 		if (value)
// 			free (value);
// 		return (1);
// 	}
// 	export_update(minishell, key, value);
// 	return (0);
// }

// Processes each export argument
int	export_process(const char *argument, t_program *minishell)
{
	char	*key;
	char	*value;

	if (export_error(argument, minishell))
		return (1);
	export_extract(argument, &key, &value);
	if (!key)
		return (1);
	if (value == NULL)
	{
		if (export_valid(key))
			add_env(minishell, key, NULL);
		else
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(key, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			minishell->status = 1;
		}
	}
	else
		export_update(minishell, key, value);
	free(key);
	free(value);
	return (0);
}

// int	ft_env(t_program *minishell)
// {
// 	t_env	*current;

// 	current = minishell->env_list;
// 	while (current)
// 	{
// 		if (current->value)
// 			printf("%s=%s\n", current->key, current->value);
// 		current = current->next;
// 	}
// 	minishell->status = 0;
// 	return (0);
// }

// void add_env(t_program *minishell, const char *key, const char *value)
// {
// 	t_env *new;

// 	new = malloc(sizeof(t_env));
// 	if (!new)
// 		return;
// 	new->key = ft_strdup(key);
// 	if (value)
// 		new->value = ft_strdup(value);
// 	else
// 		new->value = NULL;
// 	new->next = minishell->env_list;
// 	minishell->env_list = new;
// }

// int main(void)
// {
// 	t_program minishell;
// 	const char *test_args[] = {
// 		"HOME=/home/user",
// 		"PATH=/usr/bin:/bin",
// 		"USER",
// 		"INVALID_KEY=value",
// 		"123INVALID=value",
// 		"VALID_KEY=valid_value",
// 		NULL
// 	};
// 	int i;

// 	// Initialize minishell environment list
// 	minishell.env_list = NULL;
// 	minishell.status = 0;

// 	// Test export_process with various arguments
// 	i = 0;
// 	while (test_args[i])
// 	{
// 		printf("Testing argument: %s\n", test_args[i]);
// 		if (export_process(test_args[i], &minishell))
// 			printf("Error: Failed to process argument: %s\n", test_args[i]);
// 		i++;
// 	}

// 	// Print the environment after processing all arguments
// 	printf("\nFinal Environment:\n");
// 	ft_env(&minishell);
// 	// memory leaks come from here
// 	return (0);
// }
