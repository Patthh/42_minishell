// #include "../../include/minishell.h"

// void execute_pipeline(t_pipeline *pipeline, t_program *minishell)
// {
// 	t_command	*command;
// 	int			i;

// 	i = 0;
// 	if (pipeline == NULL)
// 		return;

// 	while (i < pipeline->cmd_count)
// 	{
// 		command = pipeline->commands[i];
// 		execute_command(command, minishell);
// 		i++;
// 	}
// 	// printf("execute_pipeline: finished executing pipeline\n");
// }

// void	execute_command(t_command *command, t_program *minishell)
// {
// 	if (command == NULL || command->arguments == NULL)
// 		return ;
// 	if (command->is_builtin)
// 		execute_builtin(command, minishell);
// 	// else
// 	// 	execute_external(command, minishell);
// }

// void	execute_builtin(t_command *command, t_program *minishell)
// {
// 	if (ft_strcmp(command->arguments[0], "echo") == 0)
// 		ft_echo(command, minishell);
// 	else if (ft_strcmp(command->arguments[0], "cd") == 0)
// 		ft_cd(command, minishell);
// 	else if (ft_strcmp(command->arguments[0], "pwd") == 0)
// 		ft_pwd(minishell);
// 	else if (ft_strcmp(command->arguments[0], "export") == 0)
// 		ft_export(command, minishell);
// 	else if (ft_strcmp(command->arguments[0], "unset") == 0)
// 		ft_unset(command, minishell);
// 	else if (ft_strcmp(command->arguments[0], "env") == 0)
// 		ft_env(minishell);
// 	else if (ft_strcmp(command->arguments[0], "exit") == 0)
// 		ft_exit(command, minishell);
// }
