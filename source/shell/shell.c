/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pracksaw <pracksaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 18:30:23 by pracksaw          #+#    #+#             */
/*   Updated: 2025/01/25 18:30:24 by pracksaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	shell_exit(const char *input, t_token *tokens, t_program *minishell)
{
	int	exit_status;

	exit_status = minishell->status & 255;
	if (tokens)
		free_list(tokens);
	free((char *)input);
	free_shell(minishell);
	exit(exit_status);
}

// print_tokens(tokens); // testing tokenizer
// print_pipeline(pipeline); // testing parser
int	handle_input(char *input, t_program *minishell)
{
	t_token		*tokens;
	t_pipeline	*pipeline;

	if (!quote_tracker(input))
	{
		free(input);
		return (0);
	}
	if (input && *input)
		add_history(input);
	tokens = tokenizer(input, minishell);
	pipeline = parser(tokens, minishell);
	if (pipeline && !validate_pipeline(pipeline, minishell))
	{
		free_list(tokens);
		free_pipeline(pipeline);
		free(input);
		return (1);
	}
	execute_pipeline(pipeline, minishell);
	free_list(tokens);
	free_pipeline(pipeline);
	free(input);
	return (1);
}

// #include "../include/minishell.h"
// # ifdef DEBUG_TOKEN
// void	print_tokens(t_token *head)
// {
// 	t_token	*current;
// 	if (!head)
// 	{
// 		printf("Token list is empty.\n");
// 		return ;
// 	}
// 	current = head;
// 	while (current)
// 	{
// 		printf("Type: %d, Value: %s\n", current->type, current->value);
// 		current = current->next;
// 	}
// }
// // Simple and basic print_pipeline function
// void print_pipeline(t_pipeline *pipeline)
// {
//     t_command *command;
//     t_redirection *curr;
//     int i;
//     int j;
//     if (!pipeline)
//     {
//         printf("Pipeline: nothing in there\n");
//         return;
//     }
//     i = 0;
//     while (i < pipeline->cmd_count)
//     {
//         command = pipeline->commands[i];
//         printf("Command %d:\n", i + 1);
//         j = 0;
//         while (command->arguments && command->arguments[j])
//         {
//             printf(" Arg %d: %s\n", j + 1, command->arguments[j]);
//             j++;
//         }
//         if (command->input)
//         {
//             printf(" Input:");
//             curr = command->input;
//             while (curr)
//             {
//                 printf(" %s", curr->filename);
//                 curr = curr->next;
//                 if (curr)
//                     printf(" ->");
//             }
//             printf("\n");
//         }
//         if (command->output)
//             printf(" Output: %s\n", command->output->filename);
//         if (command->append)
//             printf(" Append: %s\n", command->append->filename);
//         if (command->heredoc)
//         {
//             printf(" Heredoc:");
//             curr = command->heredoc;
//             while (curr)
//             {
//                 printf(" %s", curr->filename);
//                 curr = curr->next;
//                 if (curr)
//                     printf(" ->");
//             }
//             printf("\n");
//         }
//         i++;
//     }
// }
// #else
// void	print_tokens(t_token *head)
// {
// 	(void)head;
// }
// void print_pipeline(t_pipeline *pipeline)
// {
// 	(void)pipeline;
// }
// #endif
void	run_shell(t_program *minishell)
{
	char	*input;
	char	*cwd;
	int		result;

	while (1)
	{
		gen_env(minishell);
		cwd = getcwd(NULL, 0);
		if (cwd == NULL || access(cwd, F_OK) != 0)
			cwd_exit(cwd);
		printf("\033[4;42m%s:\033m\033[0;m\033[1;37m [%d] \033m ", cwd, minishell->status);
		signal(SIGINT, nl_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline(PROMPT);
		free(cwd);
		if (!input)
		{
			free_env (minishell);
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		result = handle_input(input, minishell);
		if (result < 0)
			break ;
	}
}

// initialize minishell's structure with default values
void	init_shell(t_program *program, char **envp)
{
	ft_memset(program, 0, sizeof(*program));
	program->envp = envp;
	program->status = 0;
	program->exit = 0;
	init_env(program);
	update_shlvl(program);
}
