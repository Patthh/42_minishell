#include "../../include/minishell.h"

static char	**get_paths_from_env(t_program *minishell)
{
	t_env	*current;

	current = minishell->env_list;
	while (current)
	{
		if (ft_strcmp(current->key, "PATH") == 0)
			return (ft_split(current->value, ':'));
		current = current->next;
	}
	return (NULL);
}

static char	*get_full_path(char *dir, char *cmd)
{
	char	*path;
	char	*full_path;

	if (!dir || !cmd)
		return (NULL);
	path = ft_strjoin(dir, "/");
	if (!path)
		return (NULL);
	full_path = ft_strjoin(path, cmd);
	free(path);
	if (!full_path)
		return (NULL);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

static void	free_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

char	*find_command_path(char *cmd, t_program *minishell)
{
	char	**paths;
	char	*full_path;
	int		i;

	if (!cmd)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	paths = get_paths_from_env(minishell);
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = get_full_path(paths[i], cmd);
		if (full_path)
		{
			free_paths(paths);
			return (full_path);
		}
		i++;
	}
	free_paths(paths);
	return (NULL);
}
