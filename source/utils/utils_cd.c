#include "../../include/minishell.h"

// expands a path starting with a tilde to its absolute path
// if HOME env not set, returns NULL
static char	*expand_tilde(const char *argument, t_program *minishell)
{
	char	*home;
	char	*expanded_path;

	home = get_path(minishell, "HOME");
	if (!home)
		return (NULL);
	if (argument[1] == '\0')
		return (ft_strdup(home));
	else if (argument[1] == '/')
		expanded_path = ft_strjoin(home, argument + 1);
	else
		expanded_path = ft_strdup(argument);
	return (expanded_path);
}

// gets value of variable
// if not set, preints error message, returns NULL
char	*get_path(t_program *minishell, char *variable)
{
	char	*path;

	path = env_value(minishell, variable);
	if (!path)
	{
		error_not_found(variable, minishell);
		return (NULL);
	}
	if (ft_strcmp(variable, "OLDPWD") == 0)
		ft_putendl_fd(path, STDOUT_FILENO);
	return (path);
}

// gets target path for cd
// case no path, returns HOME
// case single dash, returns OLDPWD
// case starts w tilde, expands it to its absolute path
char	*get_target(t_command *command, t_program *minishell)
{
	if (!command->arguments || !command->arguments[1])
		return (get_path(minishell, "HOME"));
	if (ft_strcmp(command->arguments[1], "-") == 0)
		return (get_path(minishell, "OLDPWD"));
	if (command->arguments[1][0] == '~')
		return (expand_tilde(command->arguments[1], minishell));
	return (ft_strdup(command->arguments[1]));
}

// updates OLDPWD and PWD
int	update_pwd(t_program *minishell)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	if (!getcwd(old_pwd, PATH_MAX))
	{
		error_file_not_found("getcwd", minishell);
		return (1);
	}
	if (env_value(minishell, "OLDPWD"))
		add_env(minishell, "OLDPWD", old_pwd, 1);
	if (!getcwd(new_pwd, PATH_MAX))
	{
		error_file_not_found("getcwd", minishell);
		return (1);
	}
	add_env(minishell, "PWD", new_pwd, 1);
	return (0);
}
